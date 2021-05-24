#pragma once

#include "Boxer.h"
#include "implot.h"

//#include <iostream>
//#include "TextTheme.h"


using namespace ImGui;
using namespace std;

class BoxerUI_View
{
private:
	
public:
	static void appFrameRate();
	static void showdemos();
	static void displaySensors(double temperature, double battery);
	static void plotStream();
	static void indexwindow(bool* boxer_analytics);

	static void sideNav();

	static void settings();

	
};
