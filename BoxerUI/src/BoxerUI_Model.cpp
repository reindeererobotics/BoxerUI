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

uchar* BoxerUI_Model::cameraStreamProc()
{//Collect frames from network here and add send to controller to add onto frame buffers in CameraStream::streamCamera()
	
	cv::Mat payload_output;
	uchar payload_data[5];
	for (int i = 0; i < 5; i++)
	{
	//cv::InputArray cam_payload_recv=payloadRecv();//Payload received from network
	//cv::imdecode(cam_payload_recv, 0,*payload_output);//decode and place output in payload_output mat data
		payload_data[i] = *payload_output.data;
		payload_output.~Mat();
	}
	return payload_data;

}


void BoxerUI_Model::print(const char* text)
{
	std::cout << text << std::endl;
}
 


