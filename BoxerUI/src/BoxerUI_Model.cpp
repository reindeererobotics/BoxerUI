#include "BoxerUI_Model.h"

#if _WIN32
//TODO: Complete impl of windows threads
DWORD WINAPI camProcThread(LPVOID lpParam)
{
	std::cout << "Thread Running..." << std::endl;

	return 0;
}
#endif // _WIN32
bool BoxerUI_Model::has_frames = false;
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

void* BoxerUI_Model::cameraPayloadRecv(void* args)
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
		*(cv::Mat*)args = iptr;
	}

	//pthread_exit(NULL);
	return args;
}

CameraMap BoxerUI_Model::cameraStreamProc(CameraMap& cam_map, std::vector<cv::VideoCapture>& vid, bool& is_camera_on)
{ //Collect frames from network here and add send to controller to add onto frame buffers in CameraStream::streamCamera()

	if (is_camera_on)
	{//If camera is open populate the payload_frames vector

		//std::vector<cv::Mat>::iterator it = payload_frames.begin();
			//for (; it != payload_frames.end(); ++it) {
			//	// do your things
			//	
			//}

		int i = 0, j = 0;
		cv::Mat temp;
		
		CameraMap::iterator itr = cam_map.begin();

		for (; itr != cam_map.end(); ++itr) {
			if (vid[i].isOpened())
			{
				for (; j < 5; j++)
				{
					std::cout << "Camera Opened" << std::endl;
					//std::vector<cv::Mat>::iterator frames_itr = frame.begin();

					//for (size_t j = 0; j < 5; i++)
					{
						vid[i].retrieve(itr->second[j]);
						//= temp;

					   //frame.push_back(temp);
					}
					//j++;
					//(vid).retrieve(temp);
					//load[i]=(temp);
				}
				i++;
				j = 0;
				std::cout << "Stream Popl" << std::endl;
			}
			i = 0;
		}
		has_frames = true;
	}
	else {
		try
		{
			for (cv::VideoCapture& var : vid)
			{
				var.~VideoCapture();
			}
		}
		catch (const std::exception&)
		{
			std::cerr << "Cannot Destroy Camera" << std::endl;
		}
	}
	return cam_map;
}

void BoxerUI_Model::print(const char* text)
{
	std::cout << text << std::endl;
}
