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
void BoxerUI_Model::inputHandler(){//InputType input_type=InputType::None) {
	
	//ImGui::Begin("##input");
	
	input.inputHandler();

	//ImGui::End();
}

void BoxerUI_Model::cameraStreamProc()
{//Collect frames from network here and add send to controller to add onto frame buffers in CameraStream::streamCamera()
	

}


