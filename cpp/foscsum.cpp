//----------------------------------------------------------
// name: "osc"
// version: "1.0"
// author: "Grame"
// license: "BSD"
// copyright: "(c)GRAME 2009"
//
// Code generated with Faust 0.9.73 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
  private:
	class SIG0 {
	  private:
		int 	fSamplingFreq;
		int 	iRec0[2];
	  public:
		int getNumInputs() 	{ return 0; }
		int getNumOutputs() 	{ return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			for (int i=0; i<2; i++) iRec0[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec0[0] = (1 + iRec0[1]);
				output[i] = sinf((9.587379924285257e-05f * float((iRec0[0] - 1))));
				// post processing
				iRec0[1] = iRec0[0];
			}
		}
	};


	static float 	ftbl0[65536];
	float 	fConst0;
	float 	fConst1;
	float 	fRec1[2];
	FAUSTFLOAT 	fslider0;
	float 	fConst2;
	float 	fRec2[2];
	FAUSTFLOAT 	fslider1;
	float 	fConst3;
	float 	fRec3[2];
	FAUSTFLOAT 	fslider2;
	float 	fConst4;
	float 	fRec4[2];
	FAUSTFLOAT 	fslider3;
	float 	fConst5;
	float 	fRec5[2];
	FAUSTFLOAT 	fslider4;
	float 	fConst6;
	float 	fRec6[2];
	FAUSTFLOAT 	fslider5;
	float 	fConst7;
	float 	fRec7[2];
	FAUSTFLOAT 	fslider6;
	float 	fConst8;
	float 	fRec8[2];
	FAUSTFLOAT 	fslider7;
	float 	fConst9;
	float 	fRec9[2];
	FAUSTFLOAT 	fslider8;
	float 	fConst10;
	float 	fRec10[2];
	FAUSTFLOAT 	fslider9;
	float 	fConst11;
	float 	fRec11[2];
	FAUSTFLOAT 	fslider10;
	float 	fConst12;
	float 	fRec12[2];
	FAUSTFLOAT 	fslider11;
	float 	fConst13;
	float 	fRec13[2];
	FAUSTFLOAT 	fslider12;
	float 	fConst14;
	float 	fRec14[2];
	FAUSTFLOAT 	fslider13;
	float 	fConst15;
	float 	fRec15[2];
	FAUSTFLOAT 	fslider14;
	float 	fConst16;
	float 	fRec16[2];
	FAUSTFLOAT 	fslider15;
	float 	fConst17;
	float 	fRec17[2];
	FAUSTFLOAT 	fslider16;
	float 	fConst18;
	float 	fRec18[2];
	FAUSTFLOAT 	fslider17;
	float 	fConst19;
	float 	fRec19[2];
	FAUSTFLOAT 	fslider18;
	float 	fConst20;
	float 	fRec20[2];
	FAUSTFLOAT 	fslider19;
	float 	fConst21;
	float 	fRec21[2];
	FAUSTFLOAT 	fslider20;
	float 	fConst22;
	float 	fRec22[2];
	FAUSTFLOAT 	fslider21;
	float 	fConst23;
	float 	fRec23[2];
	FAUSTFLOAT 	fslider22;
	float 	fConst24;
	float 	fRec24[2];
	FAUSTFLOAT 	fslider23;
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "osc");
		m->declare("version", "1.0");
		m->declare("author", "Grame");
		m->declare("license", "BSD");
		m->declare("copyright", "(c)GRAME 2009");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/version", "1.0");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/version", "1.0");
		m->declare("math.lib/license", "LGPL with exception");
	}

	virtual int getNumInputs() 	{ return 0; }
	virtual int getNumOutputs() 	{ return 1; }
	static void classInit(int samplingFreq) {
		SIG0 sig0;
		sig0.init(samplingFreq);
		sig0.fill(65536,ftbl0);
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = float(min(192000, max(1, fSamplingFreq)));
		fConst1 = (float(2320) / fConst0);
		for (int i=0; i<2; i++) fRec1[i] = 0;
		fslider0 = 0.0f;
		fConst2 = (float(2220) / fConst0);
		for (int i=0; i<2; i++) fRec2[i] = 0;
		fslider1 = 0.0f;
		fConst3 = (float(2120) / fConst0);
		for (int i=0; i<2; i++) fRec3[i] = 0;
		fslider2 = 0.0f;
		fConst4 = (float(2020) / fConst0);
		for (int i=0; i<2; i++) fRec4[i] = 0;
		fslider3 = 0.0f;
		fConst5 = (float(1920) / fConst0);
		for (int i=0; i<2; i++) fRec5[i] = 0;
		fslider4 = 0.0f;
		fConst6 = (float(1820) / fConst0);
		for (int i=0; i<2; i++) fRec6[i] = 0;
		fslider5 = 0.0f;
		fConst7 = (float(1720) / fConst0);
		for (int i=0; i<2; i++) fRec7[i] = 0;
		fslider6 = 0.0f;
		fConst8 = (float(1620) / fConst0);
		for (int i=0; i<2; i++) fRec8[i] = 0;
		fslider7 = 0.0f;
		fConst9 = (float(1520) / fConst0);
		for (int i=0; i<2; i++) fRec9[i] = 0;
		fslider8 = 0.0f;
		fConst10 = (float(1420) / fConst0);
		for (int i=0; i<2; i++) fRec10[i] = 0;
		fslider9 = 0.0f;
		fConst11 = (float(1320) / fConst0);
		for (int i=0; i<2; i++) fRec11[i] = 0;
		fslider10 = 0.0f;
		fConst12 = (float(1220) / fConst0);
		for (int i=0; i<2; i++) fRec12[i] = 0;
		fslider11 = 0.0f;
		fConst13 = (float(1120) / fConst0);
		for (int i=0; i<2; i++) fRec13[i] = 0;
		fslider12 = 0.0f;
		fConst14 = (float(1020) / fConst0);
		for (int i=0; i<2; i++) fRec14[i] = 0;
		fslider13 = 0.0f;
		fConst15 = (float(920) / fConst0);
		for (int i=0; i<2; i++) fRec15[i] = 0;
		fslider14 = 0.0f;
		fConst16 = (float(820) / fConst0);
		for (int i=0; i<2; i++) fRec16[i] = 0;
		fslider15 = 0.0f;
		fConst17 = (float(720) / fConst0);
		for (int i=0; i<2; i++) fRec17[i] = 0;
		fslider16 = 0.0f;
		fConst18 = (float(620) / fConst0);
		for (int i=0; i<2; i++) fRec18[i] = 0;
		fslider17 = 0.0f;
		fConst19 = (float(520) / fConst0);
		for (int i=0; i<2; i++) fRec19[i] = 0;
		fslider18 = 0.0f;
		fConst20 = (float(420) / fConst0);
		for (int i=0; i<2; i++) fRec20[i] = 0;
		fslider19 = 0.0f;
		fConst21 = (float(320) / fConst0);
		for (int i=0; i<2; i++) fRec21[i] = 0;
		fslider20 = 0.0f;
		fConst22 = (float(220) / fConst0);
		for (int i=0; i<2; i++) fRec22[i] = 0;
		fslider21 = 0.0f;
		fConst23 = (float(120) / fConst0);
		for (int i=0; i<2; i++) fRec23[i] = 0;
		fslider22 = 0.0f;
		fConst24 = (float(20) / fConst0);
		for (int i=0; i<2; i++) fRec24[i] = 0;
		fslider23 = 0.0f;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("0x00");
		interface->addHorizontalSlider("meh0", &fslider23, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh1", &fslider22, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh10", &fslider13, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh11", &fslider12, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh12", &fslider11, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh13", &fslider10, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh14", &fslider9, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh15", &fslider8, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh16", &fslider7, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh17", &fslider6, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh18", &fslider5, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh19", &fslider4, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh2", &fslider21, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh20", &fslider3, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh21", &fslider2, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh22", &fslider1, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh23", &fslider0, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh3", &fslider20, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh4", &fslider19, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh5", &fslider18, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh6", &fslider17, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh7", &fslider16, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh8", &fslider15, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("meh9", &fslider14, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = float(fslider2);
		float 	fSlow3 = float(fslider3);
		float 	fSlow4 = float(fslider4);
		float 	fSlow5 = float(fslider5);
		float 	fSlow6 = float(fslider6);
		float 	fSlow7 = float(fslider7);
		float 	fSlow8 = float(fslider8);
		float 	fSlow9 = float(fslider9);
		float 	fSlow10 = float(fslider10);
		float 	fSlow11 = float(fslider11);
		float 	fSlow12 = float(fslider12);
		float 	fSlow13 = float(fslider13);
		float 	fSlow14 = float(fslider14);
		float 	fSlow15 = float(fslider15);
		float 	fSlow16 = float(fslider16);
		float 	fSlow17 = float(fslider17);
		float 	fSlow18 = float(fslider18);
		float 	fSlow19 = float(fslider19);
		float 	fSlow20 = float(fslider20);
		float 	fSlow21 = float(fslider21);
		float 	fSlow22 = float(fslider22);
		float 	fSlow23 = float(fslider23);
		FAUSTFLOAT* output0 = output[0];
		for (int i=0; i<count; i++) {
			float fTemp0 = (fConst1 + fRec1[1]);
			fRec1[0] = (fTemp0 - floorf(fTemp0));
			float fTemp1 = (fConst2 + fRec2[1]);
			fRec2[0] = (fTemp1 - floorf(fTemp1));
			float fTemp2 = (fConst3 + fRec3[1]);
			fRec3[0] = (fTemp2 - floorf(fTemp2));
			float fTemp3 = (fConst4 + fRec4[1]);
			fRec4[0] = (fTemp3 - floorf(fTemp3));
			float fTemp4 = (fConst5 + fRec5[1]);
			fRec5[0] = (fTemp4 - floorf(fTemp4));
			float fTemp5 = (fConst6 + fRec6[1]);
			fRec6[0] = (fTemp5 - floorf(fTemp5));
			float fTemp6 = (fConst7 + fRec7[1]);
			fRec7[0] = (fTemp6 - floorf(fTemp6));
			float fTemp7 = (fConst8 + fRec8[1]);
			fRec8[0] = (fTemp7 - floorf(fTemp7));
			float fTemp8 = (fConst9 + fRec9[1]);
			fRec9[0] = (fTemp8 - floorf(fTemp8));
			float fTemp9 = (fConst10 + fRec10[1]);
			fRec10[0] = (fTemp9 - floorf(fTemp9));
			float fTemp10 = (fConst11 + fRec11[1]);
			fRec11[0] = (fTemp10 - floorf(fTemp10));
			float fTemp11 = (fConst12 + fRec12[1]);
			fRec12[0] = (fTemp11 - floorf(fTemp11));
			float fTemp12 = (fConst13 + fRec13[1]);
			fRec13[0] = (fTemp12 - floorf(fTemp12));
			float fTemp13 = (fConst14 + fRec14[1]);
			fRec14[0] = (fTemp13 - floorf(fTemp13));
			float fTemp14 = (fConst15 + fRec15[1]);
			fRec15[0] = (fTemp14 - floorf(fTemp14));
			float fTemp15 = (fConst16 + fRec16[1]);
			fRec16[0] = (fTemp15 - floorf(fTemp15));
			float fTemp16 = (fConst17 + fRec17[1]);
			fRec17[0] = (fTemp16 - floorf(fTemp16));
			float fTemp17 = (fConst18 + fRec18[1]);
			fRec18[0] = (fTemp17 - floorf(fTemp17));
			float fTemp18 = (fConst19 + fRec19[1]);
			fRec19[0] = (fTemp18 - floorf(fTemp18));
			float fTemp19 = (fConst20 + fRec20[1]);
			fRec20[0] = (fTemp19 - floorf(fTemp19));
			float fTemp20 = (fConst21 + fRec21[1]);
			fRec21[0] = (fTemp20 - floorf(fTemp20));
			float fTemp21 = (fConst22 + fRec22[1]);
			fRec22[0] = (fTemp21 - floorf(fTemp21));
			float fTemp22 = (fConst23 + fRec23[1]);
			fRec23[0] = (fTemp22 - floorf(fTemp22));
			float fTemp23 = (fConst24 + fRec24[1]);
			fRec24[0] = (fTemp23 - floorf(fTemp23));
			output0[i] = (FAUSTFLOAT)((((((((((((((((((((((((fSlow23 * ftbl0[int((65536.0f * fRec24[0]))]) + (fSlow22 * ftbl0[int((65536.0f * fRec23[0]))])) + (fSlow21 * ftbl0[int((65536.0f * fRec22[0]))])) + (fSlow20 * ftbl0[int((65536.0f * fRec21[0]))])) + (fSlow19 * ftbl0[int((65536.0f * fRec20[0]))])) + (fSlow18 * ftbl0[int((65536.0f * fRec19[0]))])) + (fSlow17 * ftbl0[int((65536.0f * fRec18[0]))])) + (fSlow16 * ftbl0[int((65536.0f * fRec17[0]))])) + (fSlow15 * ftbl0[int((65536.0f * fRec16[0]))])) + (fSlow14 * ftbl0[int((65536.0f * fRec15[0]))])) + (fSlow13 * ftbl0[int((65536.0f * fRec14[0]))])) + (fSlow12 * ftbl0[int((65536.0f * fRec13[0]))])) + (fSlow11 * ftbl0[int((65536.0f * fRec12[0]))])) + (fSlow10 * ftbl0[int((65536.0f * fRec11[0]))])) + (fSlow9 * ftbl0[int((65536.0f * fRec10[0]))])) + (fSlow8 * ftbl0[int((65536.0f * fRec9[0]))])) + (fSlow7 * ftbl0[int((65536.0f * fRec8[0]))])) + (fSlow6 * ftbl0[int((65536.0f * fRec7[0]))])) + (fSlow5 * ftbl0[int((65536.0f * fRec6[0]))])) + (fSlow4 * ftbl0[int((65536.0f * fRec5[0]))])) + (fSlow3 * ftbl0[int((65536.0f * fRec4[0]))])) + (fSlow2 * ftbl0[int((65536.0f * fRec3[0]))])) + (fSlow1 * ftbl0[int((65536.0f * fRec2[0]))])) + (fSlow0 * ftbl0[int((65536.0f * fRec1[0]))]));
			// post processing
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
		}
	}
};


float 	mydsp::ftbl0[65536];
