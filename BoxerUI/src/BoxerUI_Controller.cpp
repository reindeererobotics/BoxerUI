#include "BoxerUI_Controller.h"

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
void BoxerUI_Controller::displayIndexWindow(bool* boxer_analytics)
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

cv::Mat procCam(cv::VideoCapture vid, cv::Mat& temp) {//, std::vector<cv::Mat> payload) {



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
	//std::vector<std::vector<cv::Mat>>payload_frames = std::vector<std::vector<cv::Mat>>(5);
	//std::vector<cv::Mat>payload_frame_recv = std::vector<cv::Mat>(5);
	//cv::Mat payload_frame_recv;// = std::vector<cv::Mat>(5);
   //payload_frame.reserve(5);
	static bool x = true;

	if (x)
	{
		x = false;
		//camera_stream.payload_frames[1];

		static int i = 0;
		for (cv::VideoCapture& var : camera_stream.vid_captures)
		{
			var = cv::VideoCapture((i == 0 ? 1 : 0) + cv::CAP_DSHOW);
			i++;
			//vid.set(cv::CAP_PROP_FPS, 30.0);
		//vid.set(cv::CAP_PROP_EXPOSURE, 0.1);
		//std::cout << vid.get(cv::CAP_PROP_FPS) << std::endl;
		//cv::CAP_PROP_POS_FRAMES: gets a particular frame #. e.g. setting this prop to 5 will get the 5th frame to be saved to a cv::Mat
		}
		std::vector<cv::Mat> temp = std::vector<cv::Mat>(5);
		for (int j = 0; j < 5; j++)
		{
			camera_stream.payload_frames[j] = temp;
		}
	}
	if (camera_stream.show_camera)
	{
		//std::promise< std::vector<cv::Mat>> payload_promise;
		//std::future< std::vector<cv::Mat>> payload_future = payload_promise.get_future();

		camera_stream.cam_futures = std::async(std::launch::async, boxerModel.cameraStreamProc, std::ref(camera_stream.payload_frames), std::ref(camera_stream.vid_captures), std::ref(camera_stream.show_camera));// , std::move(payload_future));

		//payload_promise.set_value(payload_frame);
		camera_stream.payload_frames= camera_stream.cam_futures.get();


	}

	
	camera_stream.initCamera(&boxerModel.has_frames);// &(boxerModel.camera_model));// camera_stream.payload_frames);

	//payload_frame.~Mat();

	//For internal testing only
	//camera_stream.initCamera();
}