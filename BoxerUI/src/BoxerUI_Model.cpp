#include "BoxerUI_Model.h"

#if _WIN32
//TODO: Complete impl of windows threads
DWORD WINAPI camProcThread(LPVOID lpParam)
{
	std::cout << "Thread Running..." << std::endl;

	return 0;
}
#endif // _WIN32

double BoxerUI_Model::getTemperature()
{
	return BoxerUI_Model::temperature;
}
double BoxerUI_Model::getBattery()
{
	return BoxerUI_Model::battery;
}
void BoxerUI_Model::setTemperature(double temperature)
{
	this->BoxerUI_Model::temperature = temperature;
}
void BoxerUI_Model::setBattery(double battery)
{
	this->BoxerUI_Model::battery = battery;
}
void BoxerUI_Model::inputHandler()
{ //InputType input_type=InputType::None) {
	input.inputHandler();
}

void *BoxerUI_Model::cameraPayloadRecv(void *args)
{ //TODO Receive frames from socket here and create a buffer for it

	cv::Mat iptr;
	//*iptr=(cv::Mat*)malloc(sizeof(args));
	//*iptr=*(cv::Mat*)args;
	//*iptr = (cv::Mat *)malloc(sizeof(cv::Mat[5]));
	//*iptr=payload;

	cv::VideoCapture vid = cv::VideoCapture(0);
	if (vid.isOpened())
	{
		for (int i = 0; i < 5; i++)
		{
			std::cout << "Camera Opened" << std::endl;
			vid.retrieve(iptr);
		}
		vid.~VideoCapture();
		*(cv::Mat *)args = iptr;
	}

	//pthread_exit(NULL);
	return args;
}

std::vector<cv::Mat> BoxerUI_Model::cameraStreamProc(bool *is_camera_on)
{ //Collect frames from network here and add send to controller to add onto frame buffers in CameraStream::streamCamera()

#ifdef _WIN32
	HANDLE hThread;
	DWORD ThreadID;

	hThread = CreateThread(NULL, 0, camProcThread, NULL, 0, &ThreadID);
	if (hThread == NULL)
	{
		std::cout << "Thread Creation Failed. Error No.: " << GetLastError() << std::endl;
	}

	std::cout << "Thread Creation Successful" << std::endl;
	std::cout << "Thread ID: " << ThreadID << std::endl;
#else
	std::vector<cv::Mat> payload;

	cv::Mat args;
	void *return_val;
	pthread_t thread_id;

	pthread_attr_t attr;
	void *status;

	//Initialize and set thread joinable
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_create(&thread_id, &attr, cameraPayloadRecv, &args);
#endif // _WIN32

#ifdef _WIN32
	BoxerUI_Model::cameraPayloadRecv(); //do some work in windows thread and close the thread
	CloseHandle(hThread);
#else
	pthread_attr_destroy(&attr);
	pthread_join(thread_id, &return_val);
#endif // _WIN32

	// payload=*(cv::Mat*)return_val;

	return payload;
}

void BoxerUI_Model::print(const char *text)
{
	std::cout << text << std::endl;
}
