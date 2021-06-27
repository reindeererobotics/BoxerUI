#include "BoxerUI_Model.h"

#if _WIN32
//TODO: Complete impl of windows threads
DWORD WINAPI camProcThread(LPVOID lpParam) {
	std::cout << "Thread Running..." << std::endl;

	return 0;
}
#endif // _WIN32

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
void BoxerUI_Model::inputHandler() {//InputType input_type=InputType::None) {
	input.inputHandler();
}

cv::Mat BoxerUI_Model::cameraStreamProc()
{//Collect frames from network here and add send to controller to add onto frame buffers in CameraStream::streamCamera()

	cv::Mat payload;
//#ifdef _WIN32
//	HANDLE hThread;
//	DWORD ThreadID;
//
//	hThread = CreateThread(NULL, 0, camProcThread, NULL, 0, &ThreadID);
//	if (hThread == NULL)
//	{
//		std::cout << "Thread Creation Failed. Error No.: " << GetLastError() << std::endl;
//	}
//
//	std::cout << "Thread Creation Successful" << std::endl;
//	std::cout << "Thread ID: " << ThreadID << std::endl;
//#else
//	pthread_t thread_id;
//	pthread_create(&thread_id, NULL, cameraPayloadRecv, NULL);
//#endif // _WIN32

	payload = cameraPayloadRecv();

//#ifdef _WIN32
//	BoxerUI_Model::cameraPayloadRecv();//do some work in windows thread and close the thread
//	CloseHandle(hThread);
//#else
//	pthread_join(thread_id, *payload);
//#endif // _WIN32

	return payload;

}


cv::Mat BoxerUI_Model::cameraPayloadRecv()
{//TODO Receive frames from socket here and create a buffer for it

	cv::Mat payload[5];
	cv::VideoCapture vid = cv::VideoCapture(0);

	for (int i = 0; i < 5; i++)
	{
		if (vid.isOpened()) {

			vid.retrieve(payload[i]);

		}
	}
	vid.~VideoCapture();

	return *payload;
}
void BoxerUI_Model::print(const char* text)
{
	std::cout << text << std::endl;
}



