#include "BoxerUI_Model.h"


double BoxerUI_Model::getTemperature() {
	return BoxerUI_Model::temperature;
}
double BoxerUI_Model::getBattery() {
	return BoxerUI_Model::battery;
}
void BoxerUI_Model::setTemperature(double temperature) {
	this->BoxerUI_Model::temperature = temperature;
}
void BoxerUI_Model::setBattery(double battery) {
	this->BoxerUI_Model::battery = battery;
}


// void cameraStreamProc(cv::Mat frames[]) {
// //Call to socket function to receive frame buffers, send to model for processing
// frames[BUFFER_SIZE];
// // while ()

// }


