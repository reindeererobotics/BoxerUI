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
protected:

};
