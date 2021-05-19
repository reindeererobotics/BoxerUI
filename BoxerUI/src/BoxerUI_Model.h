#pragma once
// #include <opencv2/opencv.hpp>
// #include <opencv2/highgui/highgui.hpp>




class BoxerUI_Model
{
	/*ImGuiIO& io = ImGui::GetIO();
	ImFont* font1 = io.Fonts->AddFontFromFileTTF("font.ttf", 18.0f);*/
private:
	double temperature, battery;// , ultrasonic;
	


public:
	double getTemperature() {
		return temperature;
	}
	double getBattery() {
		return battery;
	}
	void setTemperature(double temperature) {
		this->temperature = temperature;
	}
	void setBattery(double battery) {
		this->battery = battery;
	}
	
	static void freezeFrame() {

	}
	// void cameraStreamProc(cv::Mat frames[]) {
	// //Call to socket function to receive frame buffers, send to model for processing
	// frames[BUFFER_SIZE];
	// // while ()

	// }

};


