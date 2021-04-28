#pragma once
#include "BoxerUI_View.h"
#include "BoxerUI_Model.h"
#include "jsoncpp/json/json.h"
#include <fstream>
#include <iostream>
#include <string>

//#include "BoxerUI_Sockets.h"
using namespace std;
class BoxerUI_Controller
{
private:
	BoxerUI_View boxerView;
	BoxerUI_Model boxerModel;
	//BoxerUI_Sockets boxerSocket;
public:
	/*BoxerUI_Controller(BoxerUI_View boxerView, BoxerUI_Model boxerModel) {
		this->boxerModel = boxerModel;
		this->boxerView = boxerView;
	}*/

	double getModelBattery() {
		return boxerModel.getBattery();
	}
	double getModelTemperature() {
		return boxerModel.getTemperature();
	}
	void setModelBattery(double batteryVal) {
		boxerModel.setBattery(batteryVal);
	}
	void setModelTemperature(double temperatureVal) {
		boxerModel.setTemperature(temperatureVal);
	}
	void cameraPayloadRecv() {
		//TODO: Call to socket function to receive frame buffers, send to model for processing
		// boxerModel.cameraStreamProc();
	}
	void decomposePayload(Json::Value jsonPayload) {
		// converts json to model data attributes
		boxerModel.setBattery(jsonPayload["Battery"].asDouble());
		boxerModel.setTemperature(jsonPayload["Temperature"].asDouble());
	}
	void displayIndexWindow(bool& boxer_analytics) {//,int ui_width,int ui_height) {		
		boxerView.indexwindow(boxer_analytics);// , ui_width, ui_height);
	}
	void displayFPS() {
		boxerView.appFrameRate();
	}
	
	void demoWindows() {//bool demo_window) {
		boxerView.showdemos();// &demo_window);
	}
	void updateBSView() {
		boxerView.displaySensors(boxerModel.getTemperature(), boxerModel.getBattery());
	}
	
	void plotView() {
		//boxerSocket.payloadRecv(4, *"payload", 0);
		boxerView.plotStream();
	}
	void streamCameraView(){//cv::VideoCapture *cap,bool* freeze_frame, cv::Mat* frame, GLuint* my_frame_texture) {
		boxerView.streamCamera();// cap, freeze_frame, frame, my_frame_texture);
	}
	void initCameraView(bool* show_camera, int* w, int* h) {
		boxerView.setCamera( show_camera, w, h);
	}
	
};

