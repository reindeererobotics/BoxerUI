#pragma once
// #include <opencv2/opencv.hpp>
// #include <opencv2/highgui/highgui.hpp>

#define BUFFER_SIZE 5

class BoxerUI_Model
{
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
	// void cameraStreamProc(cv::Mat frames[]) {
	// //Call to socket function to receive frame buffers, send to model for processing
	// frames[BUFFER_SIZE];
	// // while ()

	// }
};

