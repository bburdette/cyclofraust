declare name 		"osc";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2009";

//-----------------------------------------------
// oscmod - oscillator module. 
//-----------------------------------------------

import("music.lib");

smooth(c) = *(1-c) : +~*(c);
gain    = vslider("[1]", 0, -70, +4, 0.1) : db2linear : smooth(0.999);


f = hslider("freq",0.0,0.5,1.0,1) * 1000 : smooth(0.999);
a = hslider("amp", 0.0,0.0,1.0,1) : smooth(0.99);

// process = osc(f) * a;
process = osc(f + 150) * a, osc(f) * a;

