extern crate libc;

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

extern crate portaudio;
use portaudio::{stream, hostapi, device};

// use portaudio::util::{duration};

// #[macro_use]
// mod tryopt;
// mod stringerror;

extern crate tinyosc;
use tinyosc as osc;

extern {
  pub fn fraust_init(samplerate: i32);
  pub fn fraust_compute(count: i32, input: *const libc::c_float, output: *mut libc::c_float );
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
// const SAMPLE_RATE: f64 = 48000.0;
const SAMPLE_RATE: f64 = 44100.0;
// const FRAMES_PER_BUFFER: u32 = 64;
const FRAMES_PER_BUFFER: u32 = 2048;

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

fn main()
{
    portaudio::initialize().unwrap();
    print_devs();
    // println!("{:?}", demo());
    run();
    portaudio::terminate().unwrap();
}

fn print_devs()
{
    for i in 0 .. portaudio::device::get_count().unwrap()
    {
        match portaudio::device::get_info(i)
        {
            None => {},
            Some(info) => println!("{}: {}", i, info.name),
        }
    }
}

fn run() 
{
    // ---------------------------------------------
    // make a channel to receive updates from the osc.
    // ---------------------------------------------

    let (tx, rx) = mpsc::channel::<KeyEvt>();

    // we'll do osc receive below, in the main thread.

    // ---------------------------------------------
    // init fraust 
    // ---------------------------------------------
    println!("initting fraust with sample rate: {}", SAMPLE_RATE);

    unsafe { fraust_init(SAMPLE_RATE as i32); }

    let bufmax = 10000;
    let mut inflts = [0.0;10000];
    // flts[0] = 1.0;

    // let mut outflts = [0.0;10000];
    // let mut outflts: Vec<Vec<f32>> = vec![vec![0.0; 10000], vec![0.0,10000]];
    // let mut outflts: Vec<f32> = vec![0.0; 1000000];
    let mut outflts: Vec<f32> = vec![0.0; 10000];
    let mut frames = vec![outflts.clone(), outflts.clone()];

    let volstring = CString::new("Volume").unwrap();

    unsafe { fraust_setval(volstring.as_ptr(), 0.05); }

    let mut loopcount = 0;
    let mut buflen = 0;
    let bufmaxu = bufmax as usize;
    let mut bufidx = bufmaxu - 1;

    // make a full buffer to begin with.
    // unsafe { fraust_compute(bufmax, flts.as_mut_ptr(), outflts.as_mut_ptr()); }

    // ---------------------------------------------
    // set up portaudio callback ftn.
    // ---------------------------------------------
    let callback = Box::new(|input: &[f32], output: &mut [f32], _time: stream::StreamTimeInfo, _flags: stream::StreamCallbackFlags| -> stream::StreamCallbackResult
    {
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

        // TO DO: verify input buflen too, in case it has fewer or no channels, thats a segfault.

        // unsafe { fraust_compute(output.len() as i32, inflts.as_ptr(), output.as_mut_ptr()); }
        unsafe { fraust_compute(output.len() as i32, input.as_ptr(), output.as_mut_ptr()); }

        stream::StreamCallbackResult::Continue
    });

    // ---------------------------------------------
    // start portaudio 
    // ---------------------------------------------
    let in_idx = 2;
	/*
    let in_idx = match device::get_default_input_index()
    {
        Some(o) => o,
        None => return,
    };*/
    let in_lat = match device::get_info(in_idx)
    {
        None => return,
        Some(d) => d.default_low_input_latency,
    };
    let inparams = stream::StreamParameters { device: in_idx, channel_count: 1, suggested_latency: in_lat, data: 0f32 };

    let out_idx = 2;
    /* let out_idx = match device::get_default_output_index()
    {
        Some(o) => o,
        None => return,
    }; */
    let out_lat = match device::get_info(out_idx)
    {
        None => return,
        Some(d) => d.default_low_output_latency,
    };

    // println!("out_latency: {:?}", duration_to_pa_time(out_lat));
    // println!("out_latency: {:?}", out_lat.nun_milliseconds());


    let outparams = stream::StreamParameters { device: out_idx, channel_count: 2, suggested_latency: out_lat, data: 0f32 };

    let mut stream = match stream::Stream::open(None,
                                                Some(outparams), 
                                                44100f64, 
                                                stream::FRAMES_PER_BUFFER_UNSPECIFIED, 
                                                stream::StreamFlags::empty(), 
                                                Some(callback))
    {
        Err(v) => { println!("Err({:?})", v); return },
        Ok(stream) => stream,
    };

   /*
    let mut stream = match stream::Stream::open_default(1, 2, 44100f64, stream::FRAMES_PER_BUFFER_UNSPECIFIED, Some(callback))
    {
        Err(v) => { println!("Err({:?})", v); return },
        Ok(stream) => stream,
    };
	*/

    let finished_callback = Box::new(|| println!("Finshed callback called"));
    println!("finished_callback: {:?}", stream.set_finished_callback(finished_callback));
    println!("start: {:?}", stream.start());

    // ---------------------------------------------
    // receive OSC messages for paramter changes. 
    // ---------------------------------------------

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


