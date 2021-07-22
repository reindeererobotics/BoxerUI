#pragma once

#include "implot.h"
#include <iostream>
#include "Inputs_Model.h"
//#include "BoxerUI_Controller.h"

//#define _BOXERUI_TEST

class BoxerUI_View
{
	
public:
	//BoxerUI_View(ImFont* fonts[2]) {
	//	 //= *fonts;
	//	//this->boxerUI_fonts 
	//	for (int i = 0; i < 2; ++i)
	//	{
	//		boxerUI_fonts[i] = *fonts[i];
	//	}
	//}
	BoxerUI_View() {}
	BoxerUI_View(ImFont* fonts) {
		this->boxerUI_font = fonts;
	}
	BoxerUI_View(ImFont* fonts[2]){
		for (size_t i = 0; i < 2; i++)
		{
			boxerUI_fonts[i] = fonts[i];
		}
	}
	/*void setFonts(ImFont* fonts[2]) {
		

	}*/
	ImFont* boxerUI_fonts[2];
	ImFont* boxerUI_font;
	static void appFrameRate();
	static void showdemos();
	static void displaySensors(double temperature, double battery);
	static void plotStream();
	static void indexwindow(bool* boxer_analytics);

	bool sideNav();

	bool settings();


	//Do !!NOT!! use within Begin()/BeginChild() window
	static void resetFrame();

	
	void indexView();
protected:
	static void HelpMarker(const char* desc);
};
