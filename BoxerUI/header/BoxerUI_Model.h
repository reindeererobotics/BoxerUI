#pragma once

#include "Boxer.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

//#include "BoxerUI_Controller.h"

#ifndef _INPUTS_H
//#define _INPUTS_H
#include "Inputs_Model.h"
#endif

class BoxerUI_Model
{

private:
	double temperature, battery;// , ultrasonic;

public:
	double getTemperature();
	double getBattery();
	void setTemperature(double temperature);
	void setBattery(double battery);
	void inputHandler();
	//cv::Mat cameraStreamProc();
	uchar* cameraStreamProc(); 

protected:
	void print(const char* text);
};