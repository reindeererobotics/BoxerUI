#include "BoxerUI_Controller.h"

bool CameraStream::show_camera = false;

double BoxerUI_Controller::getModelBattery() {
	return boxerModel.getBattery();
}
double BoxerUI_Controller::getModelTemperature() {
	return boxerModel.getTemperature();
}
void BoxerUI_Controller::setModelBattery(double batteryVal) {
	boxerModel.setBattery(batteryVal);
}
void BoxerUI_Controller::setModelTemperature(double temperatureVal) {
	boxerModel.setTemperature(temperatureVal);
}
void BoxerUI_Controller::inputHandlerModel() {
	boxerModel.inputHandler();
}

void BoxerUI_Controller::cameraPayloadRecv() {
	//TODO: Call to socket function to receive frame buffers, send to model for processing

	//camera_stream.setCamContext();
	boxerModel.cameraStreamProc();

}
void BoxerUI_Controller::decomposePayload(Json::Value jsonPayload) {
	// converts json to model data attributes
	boxerModel.setBattery(3);//jsonPayload["Battery"].asDouble());
	boxerModel.setTemperature(5);//jsonPayload["Temperature"].asDouble());
}
void BoxerUI_Controller::displayIndexWindow(bool* boxer_analytics) {//,int ui_width,int ui_height) {		
	boxerView.indexwindow(boxer_analytics);// , ui_width, ui_height);
}
void BoxerUI_Controller::displayFPS() {
	boxerView.appFrameRate();
}
void BoxerUI_Controller::demoWindows() {//bool demo_window) {
	boxerView.showdemos();// &demo_window);
}
void BoxerUI_Controller::updateBSView() {
	//boxerView.displaySensors(boxerModel.getTemperature(), boxerModel.getBattery());
}
void BoxerUI_Controller::plotView() {
	//boxerSocket.payloadRecv(4, *"payload", 0);
	boxerView.plotStream();
}
void BoxerUI_Controller::navView() {
	boxerView.sideNav();
}

void BoxerUI_Controller::indexView() {
	boxerView.indexView();
	
}

void BoxerUI_Controller::cameraView() { 
	cv::Mat payload_frame;
	
	camera_stream.initCamera((camera_stream.show_camera ? boxerModel.cameraStreamProc():payload_frame));

	payload_frame.~Mat();
	
	//For internal testing only
	//camera_stream.initCamera(); 
}


