#pragma once

#include "implot.h"
#include <iostream>
#include "Inputs_Model.h"
//#include "BoxerUI_Controller.h"

//#define _BOXERUI_TEST

class BoxerUI_View
{
	
public:
	static void appFrameRate();
	static void showdemos();
	static void displaySensors(double temperature, double battery);
	static void plotStream();
	static void indexwindow(bool* boxer_analytics);

	static bool sideNav();

	static bool settings();

	//Do !!NOT!! use within Begin()/BeginChild() window
	static void resetFrame();

	
	void indexView();
protected:
	static void HelpMarker(const char* desc);
};
