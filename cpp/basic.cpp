// #pragma once
//#ifndef minimal_cpp
//#define minimal_cpp

/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2006-2011 Albert Graef <Dr.Graef@t-online.de>
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as 
	published by the Free Software Foundation; either version 2.1 of the 
	License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
 	License along with the GNU C Library; if not, write to the Free
  	Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  	02111-1307 USA. 
 ************************************************************************
 ************************************************************************/

/* Q architecture file. Derived from minimal.cpp included in the Faust
   distribution. Please note that this is to be compiled as a shared library,
   which is then loaded dynamically by Q's faust module. */

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <list>
#include <string>


using namespace std;

// 'null' implementation of Meta; nothing is recorded!
struct Meta
{
    void declare (const char* key, const char* value) { }
};

// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }

inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }

// <<includeIntrinsic>>

/******************************************************************************
*******************************************************************************

			ABSTRACT USER INTERFACE

*******************************************************************************
*******************************************************************************/

class UI
{
  bool	fStopped;
public:
		
  UI() : fStopped(false) {}
  virtual ~UI() {}
	
  virtual void addButton(char* label, float* zone) = 0;
  virtual void addCheckButton(char* label, float* zone) = 0;
  virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
  virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
  virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step) = 0;

  virtual void addHorizontalBargraph(char* label, float* zone, float min, float max) = 0;
  virtual void addVerticalBargraph(char* label, float* zone, float min, float max) = 0;
	
  virtual void openTabBox(char* label) = 0;
  virtual void openHorizontalBox(char* label) = 0;
  virtual void openVerticalBox(char* label) = 0;
  virtual void closeBox() = 0;
	
  virtual void run() = 0;
	
  void stop()	{ fStopped = true; }
  bool stopped() 	{ return fStopped; }

  virtual void declare(float* zone, const char* key, const char* value) {}
};

/***************************************************************************
   Basic UI interface (from Q UI)
 ***************************************************************************/

enum ui_elem_type_t {
  UI_BUTTON, UI_CHECK_BUTTON,
  UI_V_SLIDER, UI_H_SLIDER, UI_NUM_ENTRY,
  UI_V_BARGRAPH, UI_H_BARGRAPH,
  UI_END_GROUP, UI_V_GROUP, UI_H_GROUP, UI_T_GROUP
};

struct ui_elem_t {
  ui_elem_type_t type;
  string label;
  float *zone;
  void *ref;
  float init, min, max, step;
};


class BasicUI : public UI
{
public:
  list<ui_elem_t> elemList;
		
  BasicUI();
  virtual ~BasicUI();

protected:
  void add_elem(ui_elem_type_t type, char *label = NULL);
  void add_elem(ui_elem_type_t type, char *label, float *zone);
  void add_elem(ui_elem_type_t type, char *label, float *zone,
		float init, float min, float max, float step);
  void add_elem(ui_elem_type_t type, char *label, float *zone,
		float min, float max);

  list<string> labelList;

  std::string buildFullLabel(const char *label)
  {
    string lSReturn;
    int i = 0; 
    for (list<string>::iterator lIter = labelList.begin(); lIter != labelList.end(); ++lIter)
    {
      // std::cout << "bfl loop " << i++ << endl;
      lSReturn += *lIter;
      lSReturn += "/";
    }

    // std::cout << "bfl labeladd " << i << endl;
    lSReturn += label;

    // std::cout << "bfl return '" << lSReturn << "'" << endl;
    return lSReturn;
  }

public:
  // --------------------------------------------------------------------
  // functions required by faust for gui building.
  // --------------------------------------------------------------------
  virtual void addButton(char* label, float* zone);
  virtual void addCheckButton(char* label, float* zone);
  virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step);
  virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step);
  virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step);

  virtual void addHorizontalBargraph(char* label, float* zone, float min, float max);
  virtual void addVerticalBargraph(char* label, float* zone, float min, float max);
  
  virtual void openTabBox(char* label);
  virtual void openHorizontalBox(char* label);
  virtual void openVerticalBox(char* label);
  virtual void closeBox();
	
  virtual void run();
  // --------------------------------------------------------------------
  // functions used to find and change parameters. 
  // --------------------------------------------------------------------
  
  ui_elem_t* findElement(const char* label);
};

BasicUI::BasicUI()
{
}

BasicUI::~BasicUI()
{
}

inline void BasicUI::add_elem(ui_elem_type_t type, char *label)
{
  // zone, init, min, max, and step == 0.0
  add_elem(type, label, NULL, 0.0, 0.0, 0.0, 0.0);
}

inline void BasicUI::add_elem(ui_elem_type_t type, char *label, float *zone)
{
  // init, min, max, and step == 0.0
  add_elem(type, label, zone, 0.0, 0.0, 0.0, 0.0);
}

inline void BasicUI::add_elem(ui_elem_type_t type, char *label, float *zone,
			  float min, float max)
{
  // init and step == 0.0
  add_elem(type, label, zone, 0.0, min, max, 0.0);
}

inline void BasicUI::add_elem(ui_elem_type_t type, char *label, float *zone,
			  float init, float min, float max, float step)
{
  // std::cout << "add_elem1, type: " << type << endl;
  // null labels are just blanks.
  string lSLabel("");
  if (label)
    lSLabel = label;

  // std::cout << "add_elem2" << endl;
  // adjust the label stack?
  switch (type) 
  {
  case UI_BUTTON:
  case UI_CHECK_BUTTON:
  case UI_V_SLIDER: 
  case UI_H_SLIDER: 
  case UI_NUM_ENTRY:
  case UI_V_BARGRAPH: 
  case UI_H_BARGRAPH:
      break;
  case UI_V_GROUP: 
  case UI_H_GROUP: 
  case UI_T_GROUP:
      // std::cout << "adding group: " << lSLabel.c_str() << endl;
      labelList.push_back(lSLabel);
      // don't actually add these to the elemList, only the labelList.
      return;
  case UI_END_GROUP:
      // std::cout << "removing group." << endl;
      labelList.pop_back();
      return;
  }

  ui_elem_t lElem;
  lElem.type = type;
  lElem.label = buildFullLabel(lSLabel.c_str());
  lElem.zone = zone;
  lElem.ref = NULL;
  lElem.init = init;
  lElem.min = min;
  lElem.max = max;
  lElem.step = step;

  std::cout << "add_elem " << lElem.label << " type: " << type << endl; 

  elemList.push_back(lElem);

  // std::cout << "add end" << endl;
}


void BasicUI::addButton(char* label, float* zone)
{ add_elem(UI_BUTTON, label, zone); }
void BasicUI::addCheckButton(char* label, float* zone)
{ add_elem(UI_CHECK_BUTTON, label, zone); }
void BasicUI::addVerticalSlider(char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_V_SLIDER, label, zone, init, min, max, step); }
void BasicUI::addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_H_SLIDER, label, zone, init, min, max, step); }
void BasicUI::addNumEntry(char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_NUM_ENTRY, label, zone, init, min, max, step); }

void BasicUI::addHorizontalBargraph(char* label, float* zone, float min, float max)
{ add_elem(UI_H_BARGRAPH, label, zone, min, max); }
void BasicUI::addVerticalBargraph(char* label, float* zone, float min, float max)
{ add_elem(UI_V_BARGRAPH, label, zone, min, max); }

void BasicUI::openTabBox(char* label)
{ add_elem(UI_T_GROUP, label); }
void BasicUI::openHorizontalBox(char* label)
{ add_elem(UI_H_GROUP, label); }
void BasicUI::openVerticalBox(char* label)
{ add_elem(UI_V_GROUP, label); }
void BasicUI::closeBox()
{ add_elem(UI_END_GROUP); }

void BasicUI::run() {}

ui_elem_t* BasicUI::findElement(const char* label)
{
  // std::cout << "findElement" << label << endl;

  for (list<ui_elem_t>::iterator lIter = elemList.begin(); 
      lIter != elemList.end();
      ++lIter)
  {
    if (lIter->label == label)
      return &*lIter;
  }

  return 0;
}

/******************************************************************************

			    FAUST DSP support

*******************************************************************************/



//----------------------------------------------------------------
//  abstract definition of a signal processor
//----------------------------------------------------------------
			
class dsp {
 protected:
	int fSamplingFreq;
 public:
	dsp() {}
	virtual ~dsp() {}
	virtual int getNumInputs() = 0;
	virtual int getNumOutputs() = 0;
	virtual void buildUserInterface(UI* interface) = 0;
	virtual void init(int samplingRate) = 0;
 	virtual void compute(int len, float** inputs, float** outputs) = 0;
};

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------
		
// #include "fosc24.cpp"
// #include "modalBar.cpp"
// #include "mmb.cpp"
// #include "foscsum.cpp"
#include "oscmodsum.cpp"

static dsp *mydsp_INSTANCE = 0;
static BasicUI *myui_INSTANCE = 0;

extern "C" {
  void fraust_init(int32_t samplerate) 
  {
    mydsp_INSTANCE = new mydsp();
    mydsp_INSTANCE->init(samplerate);

    myui_INSTANCE = new BasicUI();
    mydsp_INSTANCE->buildUserInterface(myui_INSTANCE);
  }

  void fraust_compute(int len, float* inputs, float* outputs)
  { 
    if (mydsp_INSTANCE)
      mydsp_INSTANCE->compute(len, &inputs, &outputs);   
  }

  int fraust_setval(const char* label, float val)
  {
    if (!myui_INSTANCE)
      return 0;

    ui_elem_t *elt = myui_INSTANCE->findElement(label);

    if (!elt)
    {
      std::cout << "faust parameter not found: " << label << std::endl;
      return 0;
    }

    std::cout << "setting faust parameter '" << label << "' to val:" << val << std::endl;
    *(elt->zone) = val;

    return 1;
    
  }
  int fraust_getval(const char* label, float *val)
  {
    if (!myui_INSTANCE)
      return 0;

    ui_elem_t *elt = myui_INSTANCE->findElement(label);

    if (!elt)
      return 0;

    *val = *(elt->zone);
    return 1;
    
  }

}

