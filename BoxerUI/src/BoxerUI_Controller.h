#pragma once
#include "BoxerUI_View.h"
#include "BoxerUI_Model.h"
#include "jsoncpp/json/json.h"
#include <fstream>
#include <iostream>
#include <string>
#include "BoxerUI_View.h"
//#include "BoxerUI_Sockets.h"
using namespace std;
class BoxerUI_Controller
{
private:
	BoxerUI_View boxerView;
	BoxerUI_Model boxerModel;
	//BoxerUI_Sockets boxerSocket;
public:
	BoxerUI_Controller(BoxerUI_View boxerView, BoxerUI_Model boxerModel) {
		this->boxerModel = boxerModel;
		this->boxerView = boxerView;
	}

	double getModelBattery() {
		return boxerModel.getBattery();
	}
	double getModelTemperature() {
		return boxerModel.getTemperature();
	}
	void setModelBattery(double batteryVal) {
		 boxerModel.setbattery(batteryVal);
	}
	
	void setModelTemperature(double temperatureVal) {
		boxerModel.setTemperature(temperatureVal);
	}

	//void payloadRecv() {
	//	//receive data from socket
	//	ifstream file("sensors.json");
	//	Json::Value jsonPayload;
	//	Json::Reader reader;
	//	
	//	reader.parse(file, jsonPayload);

	//	decomposePayload(jsonPayload);
	//	file.close();
	//}

	void decomposePayload(Json::Value jsonPayload) {
		// converts json to model data attributes
	boxerModel.setbattery(jsonPayload["Battery"].asDouble());
	boxerModel.setTemperature(jsonPayload["Temperature"].asDouble());
	}

	void updateBSView() {
		 boxerView.displaySensors(boxerModel.getTemperature(), boxerModel.getBattery());
	}

	void plotView(){
		//boxerSocket.payloadRecv(4, *"payload", 0);
		boxerView.plotStream();
	}
};

