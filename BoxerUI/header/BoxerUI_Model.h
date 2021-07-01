#pragma once

#include "Boxer.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifdef _WIN32

#include <Windows.h>
#include <iostream>
#else
#include <stdio.h>
#include <pthread.h>

#endif // headers for threads


#ifndef _INPUTS_H
//#define _INPUTS_H
#include "Inputs_Model.h"
#endif

class BoxerUI_Model
{

private:
	double temperature, battery;// , ultrasonic;
	static void* cameraPayloadRecv(void* arg);

public:
	double getTemperature();
	double getBattery();
	void setTemperature(double temperature);
	void setBattery(double battery);
	void inputHandler();
	//cv::Mat cameraStreamProc();
	std::vector<cv::Mat> cameraStreamProc(bool* is_camera_on); 

protected:
	void print(const char* text);
};

struct thread_data{
	cv::Mat payload;
};