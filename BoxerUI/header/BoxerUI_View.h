#pragma once

#include "implot.h"
#include <iostream>
#include "Inputs_Model.h"
//#include "BoxerUI_Controller.h"



class BoxerUI_View
{
	
public:
	static void appFrameRate();
	static void showdemos();
	static void displaySensors(double temperature, double battery);
	static void plotStream();
	static void indexwindow(bool* boxer_analytics);

	static void sideNav();

	static bool settings();
	void indexView();
protected:
	static void HelpMarker(const char* desc);
};
