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

const CHANNELS: i32 = 2;
const NUM_SECONDS: i32 = 5;
const SAMPLE_RATE: f64 = 44100.0;
// const FRAMES_PER_BUFFER: u32 = 64;
const FRAMES_PER_BUFFER: u32 = 2048;

/*
    run().unwrap()
}


fn run() -> Result<(), pa::Error> {
*/
fn main() {
    // ---------------------------------------------
    // start the osc receiver thread
    // ---------------------------------------------

    // make a channel to receive updates from the osc.
    let (tx, rx) = mpsc::channel::<KeyEvt>();

    // we'll do osc receive below, in the main thread.

    // ---------------------------------------------
    // init fraust 
    // ---------------------------------------------
    println!("initting with sample rate: {}", SAMPLE_RATE);

    unsafe { fraust_init(SAMPLE_RATE as i32); }

    let bufmax = 10000;
    let mut inflts = [0.0;10000];
    // flts[0] = 1.0;

    // let mut outflts = [0.0;10000];
    // let mut outflts: Vec<Vec<f32>> = vec![vec![0.0; 10000], vec![0.0,10000]];
    let mut outflts: Vec<f32> = vec![0.0; 1000];

    let volstring = CString::new("Volume").unwrap();

    unsafe { fraust_setval(volstring.as_ptr(), 0.05); }

    let mut loopcount = 0;
    let mut buflen = 0;
    let bufmaxu = bufmax as usize;
    let mut bufidx = bufmaxu - 1;

    // make a full buffer to begin with.
    // unsafe { fraust_compute(bufmax, flts.as_mut_ptr(), outflts.as_mut_ptr()); }

    // ---------------------------------------------
    // start the rsoundio process!
    // ---------------------------------------------

    // create an audio context
    let mut sio = rsoundio::SoundIo::new();
    sio.set_name("rsoundio-example").unwrap();
    // connect to the default audio backend
    sio.connect().unwrap();
    println!("Connected to backend: {}", sio.current_backend().unwrap());
    sio.flush_events();
    // get default output device
    let dev = sio.default_output_device().unwrap();
    assert!(dev.probe_error().is_none());
    println!("Using output device: {}", dev);

    // create output stream
    let mut out = dev.create_outstream().unwrap();
    assert!(out.set_name("sine").is_ok());
    out.set_format(rsoundio::SioFormat::Float32LE).unwrap();
    println!("Output format: {}", out.format().unwrap());

    // let mut outvec = vec!dd

    // ----------------------------------
    // register callbacks
    // ----------------------------------
    out.register_write_callback(|out: rsoundio::OutStream,
                                 min_frame_count: u32,
                                 max_frame_count: u32| {
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

        // do we have enough buf? 
        if min_frame_count > bufmax
        {
          println!("not enough of the buf!");
        }
        else
        {
          // do dsp!

          // compute samples. 
          unsafe { fraust_compute(min_frame_count as i32, inflts.as_mut_ptr(), outflts.as_mut_slice().as_mut_ptr()); }

          // let chan = vec![&outflts];
          // let frames = vec![vec!&outflts, &outflts];
          // let frames = vec![&outflts,&outflts];
          // let frames = vec![outflts,outflts];
          // let r = outflts.clone();
          let frames = vec![outflts.clone(), outflts.clone()];
          out.write_stream_f32(min_frame_count, &frames).unwrap();

       }

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
    println!("Sample rate: {}", sr);

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
    /*
    thread::sleep(Duration::new(3, 0));
    println!("Pause for 1s");
    out.pause();
    thread::sleep(Duration::new(1, 0));
    println!("Unpausing");
    out.unpause();
    thread::sleep(Duration::new(3, 0));
    out.destroy()
    */

    /*
    let pa = try!(pa::PortAudio::new());

    let mut settings = try!(pa.default_output_stream_settings(CHANNELS, SAMPLE_RATE, FRAMES_PER_BUFFER));
    // we won't output out of range samples so don't bother clipping them.
    settings.flags = pa::stream_flags::CLIP_OFF;

    let id = pa::DeviceIndex(0);
    let params = pa::StreamParameters::<f32>::new(id, 2, true, 0.0);
    let mut settings = pa::OutputStreamSettings::new(params, SAMPLE_RATE, FRAMES_PER_BUFFER);
    settings.flags = pa::stream_flags::CLIP_OFF;

    printPaDev(id, &pa);
*/

  /*
    // This routine will be called by the PortAudio engine when audio is needed. It may called at
    // interrupt level on some machines so don't do anything that could mess up the system like
    // dynamic resource allocation or IO.
    let callback = move |pa::OutputStreamCallbackArgs { buffer, frames, .. }| {
        println!("in the callback!");
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

        if frames * 2 > bufmax
        {
          pa::Abort
        }
        else
        {
          // do dsp!
          let mut idx = 0;
          let mut ofidx = 0;

          // compute 'frames' number of samples.
          unsafe { fraust_compute(frames as i32, flts.as_mut_ptr(), outflts.as_mut_ptr()); }

          for _ in 0..frames {
              buffer[idx] = outflts[ofidx];
              idx += 1;
              buffer[idx] = outflts[ofidx];
              idx += 1;
              ofidx += 1;
          }
          pa::Continue
        }
    };

    let mut stream = try!(pa.open_non_blocking_stream(settings, callback));

    try!(stream.start());

    let oscrecvip = std::net::SocketAddr::from_str("0.0.0.0:8000").expect("Invalid IP");
    // spawn the osc receiver thread. 
    match oscthread(oscrecvip, tx) {
      Ok(s) => println!("oscthread exited ok"),
      Err(e) => println!("oscthread error: {} ", e),
    };
      */

    /*
    loop {
      println!("Play for {} seconds.", NUM_SECONDS);
      pa.sleep(NUM_SECONDS * 1_000);
    }
    */



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


