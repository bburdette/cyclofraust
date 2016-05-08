declare name 		"osc";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2009";

//-----------------------------------------------
// 			Sinusoidal Oscillator
//-----------------------------------------------

import("music.lib");

smooth(c)		= *(1-c) : +~*(c);
// initial value 0, ie full blast:
//vol 			= hslider("volume [unit:dB]", 0, -96, 0, 0.1) : db2linear : smooth(0.999) ;
// initial value -96, ie off.
//vol 			= hslider("volume [unit:dB]", -96, -96, 0, 0.1) : db2linear : smooth(0.999) ;
//freq 			= hslider("freq [unit:Hz]", 1000, 20, 24000, 1);

meh0			= hslider("meh0", 0.0,0.0, 1.0, 1);
meh1			= hslider("meh1", 0.0,0.0, 1.0, 1);
meh2			= hslider("meh2", 0.0,0.0, 1.0, 1);
meh3			= hslider("meh3", 0.0,0.0, 1.0, 1);
meh4			= hslider("meh4", 0.0,0.0, 1.0, 1);
meh5			= hslider("meh5", 0.0,0.0, 1.0, 1);
meh6			= hslider("meh6", 0.0,0.0, 1.0, 1);
meh7			= hslider("meh7", 0.0,0.0, 1.0, 1);
meh8			= hslider("meh8", 0.0,0.0, 1.0, 1);
meh9			= hslider("meh9", 0.0,0.0, 1.0, 1);
meh10			= hslider("meh10", 0.0,0.0, 1.0, 1);
meh11			= hslider("meh11", 0.0,0.0, 1.0, 1);
meh12			= hslider("meh12", 0.0,0.0, 1.0, 1);
meh13			= hslider("meh13", 0.0,0.0, 1.0, 1);
meh14			= hslider("meh14", 0.0,0.0, 1.0, 1);
meh15			= hslider("meh15", 0.0,0.0, 1.0, 1);
meh16			= hslider("meh16", 0.0,0.0, 1.0, 1);
meh17			= hslider("meh17", 0.0,0.0, 1.0, 1);
meh18			= hslider("meh18", 0.0,0.0, 1.0, 1);
meh19			= hslider("meh19", 0.0,0.0, 1.0, 1);
meh20			= hslider("meh20", 0.0,0.0, 1.0, 1);
meh21			= hslider("meh21", 0.0,0.0, 1.0, 1);
meh22			= hslider("meh22", 0.0,0.0, 1.0, 1);
meh23			= hslider("meh23", 0.0,0.0, 1.0, 1);

process 		=  osc(meh0 * 2380 + 20) * meh0 
	           + osc(meh1 * -2380 + 2400) * meh1 
						 + osc(meh2 * 2380 + 20) * meh2 
	           + osc(meh3 * -2380 + 2400) * meh3 
						 + osc(meh4 * 2380 + 20) * meh4 
	           + osc(meh5 * -2380 + 2400) * meh5 
						 + osc(meh6 * 2380 + 20) * meh6 
	           + osc(meh7 * -2380 + 2400) * meh7 
						 + osc(meh8 * 2380 + 20) * meh8 
	           + osc(meh9 * -2380 + 2400) * meh9 
             + osc(meh10 * 2380 + 20) * meh10 
	           + osc(meh11 * -2380 + 2400) * meh11 
						 + osc(meh12 * 2380 + 20) * meh12 
	           + osc(meh13 * -2380 + 2400) * meh13 
						 + osc(meh14 * 2380 + 20) * meh14 
	           + osc(meh15 * -2380 + 2400) * meh15 
						 + osc(meh16 * 2380 + 20) * meh16 
	           + osc(meh17 * -2380 + 2400) * meh17 
						 + osc(meh18 * 2380 + 20) * meh18
	           + osc(meh19 * -2380 + 2400) * meh19 
             + osc(meh20 * 2380 + 20) * meh20 
	           + osc(meh21 * -2380 + 2400) * meh21 
						 + osc(meh22 * 2380 + 20) * meh22 
	           + osc(meh23 * -2380 + 2400) * meh23;

