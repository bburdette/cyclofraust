declare name 		"osc";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2009";

//-----------------------------------------------
// oscmod - oscillator module. 
//-----------------------------------------------

import("music.lib");

f = hslider("freq",0.0,0.5,1.0,1) * 1000;
a = hslider("amp", 0.0,0.0,1.0,1);

process = osc(f) * a, osc(f+100) * a;
// process = osc(hslider("freq",0.0,0.5,1.0,1) * 1000) * hslider("amp", 0.0,0.0,1.0,1);

