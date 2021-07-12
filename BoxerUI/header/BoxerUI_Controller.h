#pragma once

#include "BoxerUI_View.h"
#include "BoxerUI_Model.h"
#include "CameraStream_View.h"

#include "jsoncpp/json/json.h"
#include <fstream>
#include <iostream>
#include <string>
#include <future>
#include <thread>

//#include "BoxerUI_Sockets.h"

class BoxerUI_Controller
{
private:
	BoxerUI_View boxerView;
	BoxerUI_Model boxerModel;
	CameraStream camera_stream;
	 //cv::VideoCapture vid= cv::VideoCapture(1+cv::CAP_DSHOW);
	// cv::Mat temp;
	//std::vector<std::future<void>> cam_futures;
	
	//std::future< std::vector<cv::Mat>> cam_futures;
	//std::future<cv::Mat> cam_futures;
	// cv::VideoCapture vid = cv::VideoCapture(1);

	//MODEL
	double getModelBattery();
	double getModelTemperature();
	void setModelBattery(double batteryVal);
	void setModelTemperature(double temperatureVal);
	void decomposePayload(Json::Value jsonPayload);
	void inputHandlerModel();//INPUT_MODEL
	
	//VIEW
	void displayFPS();
	void demoWindows();
	void updateBSView();
	void plotView();
	void navView();
public:
	void displayIndexWindow(bool *boxer_analytics);
	void cameraView();
	void indexView();
	void cameraPayloadRecv();
};
