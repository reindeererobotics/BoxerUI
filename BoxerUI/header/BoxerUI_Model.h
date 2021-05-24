#pragma once

class BoxerUI_Model
{
	/*ImGuiIO& io = ImGui::GetIO();
	ImFont* font1 = io.Fonts->AddFontFromFileTTF("font.ttf", 18.0f);*/
private:
	double temperature, battery;// , ultrasonic;

public:
	double getTemperature();
	double getBattery();
	void setTemperature(double temperature);
	void setBattery(double battery);
	// void cameraStreamProc(cv::Mat frames[]);
};
