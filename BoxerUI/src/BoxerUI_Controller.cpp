#include "BoxerUI_Controller.h"


//BoxerUI_Sockets boxerSocket;

/*BoxerUI_Controller(BoxerUI_View boxerView, BoxerUI_Model boxerModel) {
	this->boxerModel = boxerModel;
	this->boxerView = boxerView;
}*/

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
void BoxerUI_Controller::cameraPayloadRecv() {
	//TODO: Call to socket function to receive frame buffers, send to model for processing
	// boxerModel.cameraStreamProc();
}
void BoxerUI_Controller::decomposePayload(Json::Value jsonPayload) {
	// converts json to model data attributes
	boxerModel.setBattery(jsonPayload["Battery"].asDouble());
	boxerModel.setTemperature(jsonPayload["Temperature"].asDouble());
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
	boxerView.displaySensors(boxerModel.getTemperature(), boxerModel.getBattery());
}

void BoxerUI_Controller::plotView() {
	//boxerSocket.payloadRecv(4, *"payload", 0);
	boxerView.plotStream();
}
void BoxerUI_Controller::streamCameraView(int* camera) {//cv::VideoCapture *cap,bool* freeze_frame, cv::Mat* frame, GLuint* my_frame_texture) {

	camera_stream.streamCamera(camera);// cap, freeze_frame, frame, my_frame_texture);
}
void BoxerUI_Controller::initCameraView(bool show_camera, float w, float h) {
	//camera_stream.CameraStream::smh();
	cout << show_camera << endl;
	camera_stream.initCamera(show_camera, w, h);
}
void BoxerUI_Controller::destroyCameraView(int* current_cam) {
	camera_stream.CameraStream::destroyCamera(current_cam);
}

