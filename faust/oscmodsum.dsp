declare name 		"oscmodsum";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2009";

//-----------------------------------------------
// 			Sinusoidal Oscillator
//-----------------------------------------------

oscmod = component("oscmod.dsp");

process = sum(i,24, vgroup("grp%i", oscmod));

