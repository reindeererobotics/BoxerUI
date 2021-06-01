#pragma once
#ifndef _INPUTS_H
//#define _INPUTS_H
#include "Inputs.h"
#endif

#include "Boxer.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

class BoxerUI_Model
{
	
	/*ImGuiIO& io = ImGui::GetIO();
	ImFont* font1 = io.Fonts->AddFontFromFileTTF("font.ttf", 18.0f);*/
private:
	double temperature, battery;// , ultrasonic;

public:
	double getTemperature();
	double getBattery();
	void setTemperature(double temperature);
	void setBattery(double battery);
	void inputHandler();
	void cameraStreamProc();
};