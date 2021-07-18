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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
//#include "BoxerUI_Sockets.h"

class BoxerUI_Controller
{
private:
	BoxerUI_View boxerView;
	BoxerUI_Model boxerModel;
	CameraStream camera_stream;
	struct sockaddr_in serveraddr;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	cv::Mat current_frame = cv::Mat(100, 100, CV_8UC4);
	
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
