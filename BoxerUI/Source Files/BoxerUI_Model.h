#pragma once
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
	void setbattery(double battery) {
		this->battery = battery;
	}	
};

