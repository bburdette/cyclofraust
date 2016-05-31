declare name 		"oscmodsum";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2009";

//-----------------------------------------------
// 			Sinusoidal Oscillator
//-----------------------------------------------

oscmod = component("oscmod.dsp");

// this method loses one channel of audio.
// meh(x,y) = x,y;
// process = par(i,24, vgroup("grp%i", oscmod)) :> meh; 

// this gets both channels but mixes them into both outputs, 
// so you hear right + left in the right channel, and the same in the left channel.
process = par(i,24, vgroup("grp%i", oscmod)) :> _; 

// process = sum(i,24, vgroup("grp%i", oscmod));
// process = vgroup("grp1", oscmod) vgroup("grp2", oscmod);

