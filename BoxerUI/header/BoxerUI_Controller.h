#pragma once
#include "BoxerUI_View.h"
#include "BoxerUI_Model.h"
#include "CameraStream_View.h"

#include "jsoncpp/json/json.h"
#include <fstream>
#include <iostream>
#include <string>


//#include "BoxerUI_Sockets.h"

class BoxerUI_Controller
{
private:
	BoxerUI_View boxerView;
	BoxerUI_Model boxerModel;
	CameraStream camera_stream;
	//BoxerUI_Sockets boxerSocket;
public:

	double getModelBattery();
	double getModelTemperature();
	void setModelBattery(double batteryVal);
	void setModelTemperature(double temperatureVal);
	void cameraPayloadRecv();
	void decomposePayload(Json::Value jsonPayload);
	void displayIndexWindow(bool* boxer_analytics);
	void displayFPS();

	void demoWindows();
	void updateBSView();

	void plotView();
	void streamCameraView(int* camera);
	void initCameraView(bool* show_camera, float* w, float* h);
	void destroyCameraView(int* current_cam);

};

