extern crate libc;
extern crate rsoundio;

use std::ffi::CString;
use std::net::UdpSocket;
use std::net::SocketAddr;
use std::io::{Error,ErrorKind};
use std::string::String;
use std::fmt::format;
use std::sync::mpsc;
use std::thread;
use std::str::FromStr;
use std::cmp::min;
use std::env;

// #[macro_use]
// mod tryopt;
// mod stringerror;

extern crate tinyosc;
use tinyosc as osc;

extern {
  pub fn fraust_init(samplerate: i32);
  pub fn fraust_compute(count: i32, input: *mut libc::c_float, output: *mut libc::c_float );
  pub fn fraust_setval(label: *const libc::c_char , val: libc::c_float); 
}


enum KeType { 
  KeyPress,
  KeyMove,
  KeyUnpress,
  KeyHit
} 

pub struct KeyEvt { 
  evttype: KeType
, keyindex: i32
, position: f32
}

// const CHANNELS: i32 = 2;
// const NUM_SECONDS: i32 = 5;
const SAMPLE_RATE: f64 = 48000.0;
// const SAMPLE_RATE: f64 = 44100.0;
// const FRAMES_PER_BUFFER: u32 = 64;
// const FRAMES_PER_BUFFER: u32 = 2048;

fn main() {
  
  let args = env::args();
  let mut iter = args.skip(1); // skip the program name

  let latency = 
    match iter.next() {
      Some(latency) => {
        FromStr::from_str(&latency).unwrap()
      }
      None => {
        0.006
      }
    };

  run(latency);
}

/*
fn main() {
    match run() {
      Err(e) => println!("error {:?}", e),
      _ => (),
    }
    run().unwrap()
}


fn run() -> Result<(), Box<std::error::Error> >
*/
fn run(latency: f64) 
{
    // make a channel to receive updates from the osc.
    let (tx, rx) = mpsc::channel::<KeyEvt>();

    // we'll do osc receive below, in the main thread.

    // ---------------------------------------------
    // init fraust 
    // ---------------------------------------------
    println!("initting fraust with sample rate: {}", SAMPLE_RATE);

    unsafe { fraust_init(SAMPLE_RATE as i32); }

    let bufmax = 10000;
    let mut inflts = [0.0;10000];

    let mut outflts: Vec<f32> = vec![0.0; 10000];
    let mut frames = vec![outflts.clone(), outflts.clone()];

    let volstring = CString::new("Volume").unwrap();

    unsafe { fraust_setval(volstring.as_ptr(), 0.05); }

    let mut loopcount = 0;
    let mut buflen = 0;
    let bufmaxu = bufmax as usize;
    let mut bufidx = bufmaxu - 1;

    // ---------------------------------------------
    // start the rsoundio process!
    // ---------------------------------------------

    // create an audio context
    let mut sio = rsoundio::SoundIo::new();
    sio.set_name("rsoundio-example").unwrap();

    // print the backends.
    let becount = sio.backend_count();

    println!("backend count {}", becount);

    for i in 0..becount {
      let be = sio.backend(i);
      println!("backend #{}: {:?} ", i, be);
    }

    // let be = try_opt_resbox!(sio.backend(2), "backend error");
    let be = sio.backend(1).unwrap();
    sio.connect_backend(be).unwrap();

    // connect to the default audio backend
    // sio.connect().unwrap();
    println!("Connected to backend: {}", sio.current_backend().unwrap());
    sio.flush_events();
    // get default output device
    let dev = sio.default_output_device().unwrap();
    assert!(dev.probe_error().is_none());
    println!("Using output device: {}", dev);

    // create output stream
    let mut out = dev.create_outstream().unwrap();
    assert!(out.set_name("noise").is_ok());
    out.set_format(rsoundio::SioFormat::Float32LE).unwrap();
    println!("setting latency: {:?}", latency);
    out.set_latency(latency);
    println!("Output format: {}", out.format().unwrap());

    // ----------------------------------
    // register callbacks
    // ----------------------------------
    out.register_write_callback(|out: rsoundio::OutStream,
                                 min_frame_count: u32,
                                 max_frame_count: u32| {
        
        // println!("latency: {:?}", out.latency());

        // any events to update the DSP with?? 
        match rx.try_recv() { 
          Ok(ke) => {
            match ke.evttype { 
              KeType::KeyHit => { 
                  // println!("setting vol to 0.3!");
                  unsafe { fraust_setval(volstring.as_ptr(), 0.3); }
                }
              KeType::KeyUnpress => { 
                  // println!("setting vol to 0.001!");
                  unsafe { fraust_setval(volstring.as_ptr(), 0.001); }
                }
              _ => {}
            }
          }
          _ => {}
        }

        // do dsp!

        // compute samples.

        let comp_count = min(max_frame_count, outflts.len() as u32);

        // println!("callback, min {}, max {}, comp_count {}", min_frame_count, max_frame_count, comp_count);

        unsafe { fraust_compute(comp_count as i32, inflts.as_mut_ptr(), frames[0].as_mut_slice().as_mut_ptr()); }

        // println!("meh: {}, {}, {}", outflts[0], min_frame_count, max_frame_count);

        // let chan = vec![&outflts];
        // let frames = vec![vec!&outflts, &outflts];
        // let frames = vec![&outflts,&outflts];
        // let frames = vec![outflts,outflts];
        // let r = outflts.clone();
        // let frames = vec![outflts.clone(), outflts.clone()];

        // frames[1].clone_from_slice(frames[0].as_slice());
        // frames[1].clone_from(&frames[0]);
        {
          let (l,r) = frames.split_at_mut(1);
          r[0].clone_from(&l[0]);
        }


        // out.write_stream_f32(min_frame_count, &frames).unwrap();
        out.write_stream_f32(comp_count, &frames).unwrap();

        // out.clear_buffer();

        /*
        let l: Vec<f32> = samples.iter()
                                 .cycle()
                                 .take(max_frame_count as usize + pos)
                                 .skip(pos)
                                 .map(|s| *s)
                                 .collect();
        pos = (max_frame_count as usize + pos) % cycle_len;
        let r = l.clone();
        let frames = vec![l, r];
        out.write_stream_f32(min_frame_count, &frames).unwrap();
        */
    });
    out.register_underflow_callback(|out: rsoundio::OutStream| {
        println!("Underflow in {} occured!", out.name().unwrap())
    });
    out.register_error_callback(|out: rsoundio::OutStream, err: rsoundio::SioError| {
        println!("{} error: {}", out.name().unwrap(), err)
    });

    // open output stream
    out.open().unwrap();
    let sr = out.sample_rate();
    println!("output sample rate: {}", sr);

    let layout = out.layout();
    println!("Output channel layout: {}", layout);
    // start audio output (now the `write_callback` will be called periodically)
    out.start().unwrap();

    let oscrecvip = std::net::SocketAddr::from_str("0.0.0.0:8000").expect("Invalid IP");
    // since sound is in a separate thread, 
    // use this thread to do the osc receiver stuff.
    match oscthread(oscrecvip, tx) {
      Ok(s) => println!("oscthread exited ok"),
      Err(e) => println!("oscthread error: {} ", e),
    };

    println!("its over!");

    // Ok(())
}

fn oscthread(oscrecvip: SocketAddr, sender: mpsc::Sender<KeyEvt>) -> Result<String, Error> { 
  let socket = try!(UdpSocket::bind(oscrecvip));
  let mut buf = [0; 1000];

  loop { 
    let (amt, src) = try!(socket.recv_from(&mut buf));

    // println!("length: {}", amt);
    let inmsg = match osc::Message::deserialize(&buf[.. amt]) {
      Ok(m) => m,
      Err(e) => {
          return Err(Error::new(ErrorKind::Other, "oh no!"));
        },
      };

    // println!("message received {} {:?}", inmsg.path, inmsg.arguments );

    match inmsg {
      osc::Message { path: "keyh", arguments: ref args } => {
        let q = &args[0];
        let r = &args[1];
        // coming from the cyclophone, a is the key index and 
        // b is nominally 0.0 to 1.0
        match (q,r) {
          (&osc::Argument::i(idx), &osc::Argument::f(amt)) => {
              // build a keyevt to send over to the sound thread.
              let ke = KeyEvt{ evttype: KeType::KeyHit, keyindex: idx, position: amt };
              sender.send(ke)
              //Ok(0)
            },
          _ => { 
            // println!("ignore");
            Ok(())
          },
        }
      }
      osc::Message { path: "keye", arguments: ref args } => {
        let q = &args[0];
        let r = &args[1];
        // coming from the cyclophone, a is the key index and 
        // b is nominally 0.0 to 1.0
        match (q,r) {
          (&osc::Argument::i(idx), &osc::Argument::f(amt)) => {
              // build a keyevt to send over to the sound thread.
              let ke = KeyEvt{ evttype: KeType::KeyUnpress, keyindex: idx, position: amt };
              sender.send(ke)
              //Ok(0)
            },
          _ => { 
            // println!("ignore");
            Ok(())
          },
        }
      }
      /*
      osc::Message { path: "keyc", arguments: ref args } => {
      },
      */
      _ => { // println!("ignore");
           Ok(()) } ,
      };
  };


  // drop(socket); // close the socket
  // Ok(String::from("meh"))
}


