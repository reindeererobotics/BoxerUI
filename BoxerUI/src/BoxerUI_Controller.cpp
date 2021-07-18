#include "BoxerUI_Controller.h"
#include "Networking/socketLibrary.cpp"
bool CameraStream::show_camera = false;

double BoxerUI_Controller::getModelBattery()
{
	return boxerModel.getBattery();
}
double BoxerUI_Controller::getModelTemperature()
{
	return boxerModel.getTemperature();
}
void BoxerUI_Controller::setModelBattery(double batteryVal)
{
	boxerModel.setBattery(batteryVal);
}
void BoxerUI_Controller::setModelTemperature(double temperatureVal)
{
	boxerModel.setTemperature(temperatureVal);
}
void BoxerUI_Controller::inputHandlerModel()
{
	boxerModel.inputHandler();
}

void BoxerUI_Controller::cameraPayloadRecv()
{
	//TODO: Call to socket function to receive frame buffers, send to model for processing

	//camera_stream.setCamContext();
	//boxerModel.cameraStreamProc();
}
void BoxerUI_Controller::decomposePayload(Json::Value jsonPayload)
{
	// converts json to model data attributes
	boxerModel.setBattery(3);	  //jsonPayload["Battery"].asDouble());
	boxerModel.setTemperature(5); //jsonPayload["Temperature"].asDouble());
}
void BoxerUI_Controller::displayIndexWindow(bool *boxer_analytics)
{											//,int ui_width,int ui_height) {
	boxerView.indexwindow(boxer_analytics); // , ui_width, ui_height);
}
void BoxerUI_Controller::displayFPS()
{
	boxerView.appFrameRate();
}
void BoxerUI_Controller::demoWindows()
{						   //bool demo_window) {
	boxerView.showdemos(); // &demo_window);
}
void BoxerUI_Controller::updateBSView()
{
	//boxerView.displaySensors(boxerModel.getTemperature(), boxerModel.getBattery());
}
void BoxerUI_Controller::plotView()
{
	//boxerSocket.payloadRecv(4, *"payload", 0);
	boxerView.plotStream();
}
void BoxerUI_Controller::navView()
{
	boxerView.sideNav();
}

void BoxerUI_Controller::indexView()
{
	boxerView.indexView();
}

// std::mutex cam_mutex;

cv::Mat procCam(cv::VideoCapture vid, cv::Mat &temp)
{ //, std::vector<cv::Mat> payload) {

	//if (is_camera_on)

	//static  = std::vector<cv::Mat>(5);
	//vid = ;
	//cap = true;
	static bool x = true;
	//std::vector<cv::Mat> load= std::vector<cv::Mat>(5);// = f.get();
	//cv::VideoCapture vid = cv::VideoCapture(1);;
	//cam_mutex.lock();
	if (vid.isOpened())
	{
		std::cout << "Camera Opened" << std::endl;
		//std::unique_lock<std::mutex> guard(cam_mutex);
		// , std::defer_lock);

		//for (int i = 0; i < 5; i++)
		{

			std::cout << "Camera retrieve" << std::endl;
			//std::unique_lock<std::mutex> guard(cam_mutex);
			(vid).retrieve(temp);
			//load[i]=(temp);
		}
		//guard.unlock();
	}

	//vid.~VideoCapture();
	//cam_mutex.unlock();
	return temp;
}

void BoxerUI_Controller::cameraView()
{
	static bool x = true;

	if (x)
	{
		x = false;

		serveraddr.sin_family = AF_INET;
		serveraddr.sin_port = htons(8000);
		serveraddr.sin_addr.s_addr = inet_addr("184.146.119.106");

		struct FrameStructure Overhead = recvFrameOverhead(sockfd, serveraddr);
		int rows = Overhead.rows;
		int cols = Overhead.cols;
	cv::Mat temp = recvFrame(sockfd, serveraddr);
	cv::Mat* temp2=&temp;
	camera_stream.initCamera(temp2); 
}