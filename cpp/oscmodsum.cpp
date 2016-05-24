//----------------------------------------------------------
// name: "oscmodsum"
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
	FAUSTFLOAT 	fslider0;
	float 	fConst0;
	float 	fRec1[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	float 	fRec2[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	float 	fRec3[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	float 	fRec4[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	float 	fRec5[2];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	float 	fRec6[2];
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fslider12;
	float 	fRec7[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	float 	fRec8[2];
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT 	fslider16;
	float 	fRec9[2];
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fslider18;
	float 	fRec10[2];
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fslider20;
	float 	fRec11[2];
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT 	fslider22;
	float 	fRec12[2];
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT 	fslider24;
	float 	fRec13[2];
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	float 	fRec14[2];
	FAUSTFLOAT 	fslider27;
	FAUSTFLOAT 	fslider28;
	float 	fRec15[2];
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT 	fslider30;
	float 	fRec16[2];
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT 	fslider32;
	float 	fRec17[2];
	FAUSTFLOAT 	fslider33;
	FAUSTFLOAT 	fslider34;
	float 	fRec18[2];
	FAUSTFLOAT 	fslider35;
	FAUSTFLOAT 	fslider36;
	float 	fRec19[2];
	FAUSTFLOAT 	fslider37;
	FAUSTFLOAT 	fslider38;
	float 	fRec20[2];
	FAUSTFLOAT 	fslider39;
	FAUSTFLOAT 	fslider40;
	float 	fRec21[2];
	FAUSTFLOAT 	fslider41;
	FAUSTFLOAT 	fslider42;
	float 	fRec22[2];
	FAUSTFLOAT 	fslider43;
	FAUSTFLOAT 	fslider44;
	float 	fRec23[2];
	FAUSTFLOAT 	fslider45;
	FAUSTFLOAT 	fslider46;
	float 	fRec24[2];
	FAUSTFLOAT 	fslider47;
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "oscmodsum");
		m->declare("version", "1.0");
		m->declare("author", "Grame");
		m->declare("license", "BSD");
		m->declare("copyright", "(c)GRAME 2009");
		m->declare("oscmod.dsp/name", "osc");
		m->declare("oscmod.dsp/version", "1.0");
		m->declare("oscmod.dsp/author", "Grame");
		m->declare("oscmod.dsp/license", "BSD");
		m->declare("oscmod.dsp/copyright", "(c)GRAME 2009");
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
		fslider0 = 0.0f;
		fConst0 = (float(1000) / float(min(192000, max(1, fSamplingFreq))));
		for (int i=0; i<2; i++) fRec1[i] = 0;
		fslider1 = 0.0f;
		fslider2 = 0.0f;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		fslider3 = 0.0f;
		fslider4 = 0.0f;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		fslider5 = 0.0f;
		fslider6 = 0.0f;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		fslider7 = 0.0f;
		fslider8 = 0.0f;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		fslider9 = 0.0f;
		fslider10 = 0.0f;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		fslider11 = 0.0f;
		fslider12 = 0.0f;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		fslider13 = 0.0f;
		fslider14 = 0.0f;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		fslider15 = 0.0f;
		fslider16 = 0.0f;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		fslider17 = 0.0f;
		fslider18 = 0.0f;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		fslider19 = 0.0f;
		fslider20 = 0.0f;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		fslider21 = 0.0f;
		fslider22 = 0.0f;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		fslider23 = 0.0f;
		fslider24 = 0.0f;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		fslider25 = 0.0f;
		fslider26 = 0.0f;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		fslider27 = 0.0f;
		fslider28 = 0.0f;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		fslider29 = 0.0f;
		fslider30 = 0.0f;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		fslider31 = 0.0f;
		fslider32 = 0.0f;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		fslider33 = 0.0f;
		fslider34 = 0.0f;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		fslider35 = 0.0f;
		fslider36 = 0.0f;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		fslider37 = 0.0f;
		fslider38 = 0.0f;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		fslider39 = 0.0f;
		fslider40 = 0.0f;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		fslider41 = 0.0f;
		fslider42 = 0.0f;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		fslider43 = 0.0f;
		fslider44 = 0.0f;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		fslider45 = 0.0f;
		fslider46 = 0.0f;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		fslider47 = 0.0f;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("0x00");
		interface->openVerticalBox("grp0");
		interface->addHorizontalSlider("amp", &fslider47, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider46, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp1");
		interface->addHorizontalSlider("amp", &fslider45, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider44, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp10");
		interface->addHorizontalSlider("amp", &fslider27, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider26, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp11");
		interface->addHorizontalSlider("amp", &fslider25, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider24, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp12");
		interface->addHorizontalSlider("amp", &fslider23, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider22, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp13");
		interface->addHorizontalSlider("amp", &fslider21, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider20, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp14");
		interface->addHorizontalSlider("amp", &fslider19, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider18, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp15");
		interface->addHorizontalSlider("amp", &fslider17, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider16, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp16");
		interface->addHorizontalSlider("amp", &fslider15, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider14, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp17");
		interface->addHorizontalSlider("amp", &fslider13, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider12, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp18");
		interface->addHorizontalSlider("amp", &fslider11, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider10, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp19");
		interface->addHorizontalSlider("amp", &fslider9, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider8, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp2");
		interface->addHorizontalSlider("amp", &fslider43, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider42, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp20");
		interface->addHorizontalSlider("amp", &fslider7, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider6, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp21");
		interface->addHorizontalSlider("amp", &fslider5, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider4, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp22");
		interface->addHorizontalSlider("amp", &fslider3, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider2, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp23");
		interface->addHorizontalSlider("amp", &fslider1, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider0, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp3");
		interface->addHorizontalSlider("amp", &fslider41, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider40, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp4");
		interface->addHorizontalSlider("amp", &fslider39, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider38, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp5");
		interface->addHorizontalSlider("amp", &fslider37, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider36, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp6");
		interface->addHorizontalSlider("amp", &fslider35, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider34, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp7");
		interface->addHorizontalSlider("amp", &fslider33, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider32, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp8");
		interface->addHorizontalSlider("amp", &fslider31, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider30, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->openVerticalBox("grp9");
		interface->addHorizontalSlider("amp", &fslider29, 0.0f, 0.0f, 1.0f, 1.0f);
		interface->addHorizontalSlider("freq", &fslider28, 0.0f, 0.5f, 1.0f, 1.0f);
		interface->closeBox();
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = (fConst0 * float(fslider0));
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = (fConst0 * float(fslider2));
		float 	fSlow3 = float(fslider3);
		float 	fSlow4 = (fConst0 * float(fslider4));
		float 	fSlow5 = float(fslider5);
		float 	fSlow6 = (fConst0 * float(fslider6));
		float 	fSlow7 = float(fslider7);
		float 	fSlow8 = (fConst0 * float(fslider8));
		float 	fSlow9 = float(fslider9);
		float 	fSlow10 = (fConst0 * float(fslider10));
		float 	fSlow11 = float(fslider11);
		float 	fSlow12 = (fConst0 * float(fslider12));
		float 	fSlow13 = float(fslider13);
		float 	fSlow14 = (fConst0 * float(fslider14));
		float 	fSlow15 = float(fslider15);
		float 	fSlow16 = (fConst0 * float(fslider16));
		float 	fSlow17 = float(fslider17);
		float 	fSlow18 = (fConst0 * float(fslider18));
		float 	fSlow19 = float(fslider19);
		float 	fSlow20 = (fConst0 * float(fslider20));
		float 	fSlow21 = float(fslider21);
		float 	fSlow22 = (fConst0 * float(fslider22));
		float 	fSlow23 = float(fslider23);
		float 	fSlow24 = (fConst0 * float(fslider24));
		float 	fSlow25 = float(fslider25);
		float 	fSlow26 = (fConst0 * float(fslider26));
		float 	fSlow27 = float(fslider27);
		float 	fSlow28 = (fConst0 * float(fslider28));
		float 	fSlow29 = float(fslider29);
		float 	fSlow30 = (fConst0 * float(fslider30));
		float 	fSlow31 = float(fslider31);
		float 	fSlow32 = (fConst0 * float(fslider32));
		float 	fSlow33 = float(fslider33);
		float 	fSlow34 = (fConst0 * float(fslider34));
		float 	fSlow35 = float(fslider35);
		float 	fSlow36 = (fConst0 * float(fslider36));
		float 	fSlow37 = float(fslider37);
		float 	fSlow38 = (fConst0 * float(fslider38));
		float 	fSlow39 = float(fslider39);
		float 	fSlow40 = (fConst0 * float(fslider40));
		float 	fSlow41 = float(fslider41);
		float 	fSlow42 = (fConst0 * float(fslider42));
		float 	fSlow43 = float(fslider43);
		float 	fSlow44 = (fConst0 * float(fslider44));
		float 	fSlow45 = float(fslider45);
		float 	fSlow46 = (fConst0 * float(fslider46));
		float 	fSlow47 = float(fslider47);
		FAUSTFLOAT* output0 = output[0];
		for (int i=0; i<count; i++) {
			float fTemp0 = (fRec1[1] + fSlow0);
			fRec1[0] = (fTemp0 - floorf(fTemp0));
			float fTemp1 = (fRec2[1] + fSlow2);
			fRec2[0] = (fTemp1 - floorf(fTemp1));
			float fTemp2 = (fRec3[1] + fSlow4);
			fRec3[0] = (fTemp2 - floorf(fTemp2));
			float fTemp3 = (fRec4[1] + fSlow6);
			fRec4[0] = (fTemp3 - floorf(fTemp3));
			float fTemp4 = (fRec5[1] + fSlow8);
			fRec5[0] = (fTemp4 - floorf(fTemp4));
			float fTemp5 = (fRec6[1] + fSlow10);
			fRec6[0] = (fTemp5 - floorf(fTemp5));
			float fTemp6 = (fRec7[1] + fSlow12);
			fRec7[0] = (fTemp6 - floorf(fTemp6));
			float fTemp7 = (fRec8[1] + fSlow14);
			fRec8[0] = (fTemp7 - floorf(fTemp7));
			float fTemp8 = (fRec9[1] + fSlow16);
			fRec9[0] = (fTemp8 - floorf(fTemp8));
			float fTemp9 = (fRec10[1] + fSlow18);
			fRec10[0] = (fTemp9 - floorf(fTemp9));
			float fTemp10 = (fRec11[1] + fSlow20);
			fRec11[0] = (fTemp10 - floorf(fTemp10));
			float fTemp11 = (fRec12[1] + fSlow22);
			fRec12[0] = (fTemp11 - floorf(fTemp11));
			float fTemp12 = (fRec13[1] + fSlow24);
			fRec13[0] = (fTemp12 - floorf(fTemp12));
			float fTemp13 = (fRec14[1] + fSlow26);
			fRec14[0] = (fTemp13 - floorf(fTemp13));
			float fTemp14 = (fRec15[1] + fSlow28);
			fRec15[0] = (fTemp14 - floorf(fTemp14));
			float fTemp15 = (fRec16[1] + fSlow30);
			fRec16[0] = (fTemp15 - floorf(fTemp15));
			float fTemp16 = (fRec17[1] + fSlow32);
			fRec17[0] = (fTemp16 - floorf(fTemp16));
			float fTemp17 = (fRec18[1] + fSlow34);
			fRec18[0] = (fTemp17 - floorf(fTemp17));
			float fTemp18 = (fRec19[1] + fSlow36);
			fRec19[0] = (fTemp18 - floorf(fTemp18));
			float fTemp19 = (fRec20[1] + fSlow38);
			fRec20[0] = (fTemp19 - floorf(fTemp19));
			float fTemp20 = (fRec21[1] + fSlow40);
			fRec21[0] = (fTemp20 - floorf(fTemp20));
			float fTemp21 = (fRec22[1] + fSlow42);
			fRec22[0] = (fTemp21 - floorf(fTemp21));
			float fTemp22 = (fRec23[1] + fSlow44);
			fRec23[0] = (fTemp22 - floorf(fTemp22));
			float fTemp23 = (fRec24[1] + fSlow46);
			fRec24[0] = (fTemp23 - floorf(fTemp23));
			output0[i] = (FAUSTFLOAT)((((((((((((((((((((((((fSlow47 * ftbl0[int((65536.0f * fRec24[0]))]) + (fSlow45 * ftbl0[int((65536.0f * fRec23[0]))])) + (fSlow43 * ftbl0[int((65536.0f * fRec22[0]))])) + (fSlow41 * ftbl0[int((65536.0f * fRec21[0]))])) + (fSlow39 * ftbl0[int((65536.0f * fRec20[0]))])) + (fSlow37 * ftbl0[int((65536.0f * fRec19[0]))])) + (fSlow35 * ftbl0[int((65536.0f * fRec18[0]))])) + (fSlow33 * ftbl0[int((65536.0f * fRec17[0]))])) + (fSlow31 * ftbl0[int((65536.0f * fRec16[0]))])) + (fSlow29 * ftbl0[int((65536.0f * fRec15[0]))])) + (fSlow27 * ftbl0[int((65536.0f * fRec14[0]))])) + (fSlow25 * ftbl0[int((65536.0f * fRec13[0]))])) + (fSlow23 * ftbl0[int((65536.0f * fRec12[0]))])) + (fSlow21 * ftbl0[int((65536.0f * fRec11[0]))])) + (fSlow19 * ftbl0[int((65536.0f * fRec10[0]))])) + (fSlow17 * ftbl0[int((65536.0f * fRec9[0]))])) + (fSlow15 * ftbl0[int((65536.0f * fRec8[0]))])) + (fSlow13 * ftbl0[int((65536.0f * fRec7[0]))])) + (fSlow11 * ftbl0[int((65536.0f * fRec6[0]))])) + (fSlow9 * ftbl0[int((65536.0f * fRec5[0]))])) + (fSlow7 * ftbl0[int((65536.0f * fRec4[0]))])) + (fSlow5 * ftbl0[int((65536.0f * fRec3[0]))])) + (fSlow3 * ftbl0[int((65536.0f * fRec2[0]))])) + (fSlow1 * ftbl0[int((65536.0f * fRec1[0]))]));
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
