#pragma once

#include "Boxer.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <map>
#include <vector>
#include <future>
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

using CameraMap = std::map <int, std::vector<cv::Mat >>;

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
static bool has_frames;

	
	static CameraMap cameraStreamProc(CameraMap& cam_map, std::vector<cv::VideoCapture>& vid, bool& is_camera_on);
	//static std::vector<std::vector<cv::Mat>> cameraStreamProc(std::vector<cv::VideoCapture>& vid, std::vector<std::vector<cv::Mat>>& payload_frames, bool& is_camera_on);

protected:
	void print(const char* text);
};
