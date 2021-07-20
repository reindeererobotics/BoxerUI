#pragma once

#include "CustomComponents_View.h"
#include "implot.h"
//#include <iostream>
//#include "TextTheme.h"
#ifndef _INPUTS_H
//#define _INPUTS_H
#include "Inputs.h"
#endif



class BoxerUI_View
{
private:
	
public:
	static void appFrameRate();
	static void showdemos();
	static void displaySensors(double temperature, double battery);
	static void plotStream();
	static void indexwindow(bool* boxer_analytics);

	static bool sideNav();

	static bool settings();

protected: 
	//Do !!NOT!! use within Begin()/BeginChild() window
	static void resetFrame();

	
};
//extern void HelpMarker(const char* desc);