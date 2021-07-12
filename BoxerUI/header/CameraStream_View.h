#pragma once
#include "Boxer.h"
#include <BoxerUI_View.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp> //Note: no need to include these headers in the working file. These will be handled automatically by linker

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <future>

#include <map>
#include <vector>

#ifdef _WIN32

#else
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#endif

using CameraMap = std::map <int, std::vector<cv::Mat >>;

//#ifndef CAMERASTREAM_VIEW_H_
//...
//#endif // !CAMERASTREAM_VIEW_H_
//Preprocessor. Checks if the symbol has been not bee ndefined. Use #pragma, it includes the symbol once

#define BUFFER_SIZE 5
#define NUM_CAMERAS 4
#define FREEZE_FRAME_IMG (NUM_CAMERAS+1)

class CameraStream : public BoxerUI_View
{

private:
	//cv::VideoCapture vid = cv::VideoCapture(1 + cv::CAP_DSHOW);
	//cv::Mat temp;
	//static std::future<cv::Mat> cam_futures;
	//std::vector<std::future<void>> cam_futures;
	//std::future< std::vector<cv::Mat>> cam_futures;
	static bool freeze_frame, enhance;

	//std::vector<std::vector<cv::Mat>> frames = std::vector<std::vector<cv::Mat>>(NUM_CAMERAS + 1); //Last frame in array is dedicated to store freeze frame
	//CameraMap frames; //Last frame in array is dedicated to store freeze frame
	//cv::Mat frames;// = std::vector<cv::Mat>(NUM_CAMERAS + 1); //Last frame in array is dedicated to store freeze frame

	void dispFrame(cv::Mat* frame);

	static void BindCVMat2GLTexture(cv::Mat& disp_frame);

	//destroy the frame & cap objects then release from memory
	void destroyCamera(int* index);

	void setCameraPropTest(int* camera, cv::VideoCapture* capture, float* w, float* h);

	static bool streamCamera(int* camera);// , bool& freeze_frame);

	static void setCamContext(int context);

	static void freezeFrame();

	void swapCamViews();

	bool got_stream = false;
	std::future<bool> stream;
public:
	static bool show_camera;// = false;
	std::vector<cv::VideoCapture> vid_captures = std::vector<cv::VideoCapture>(5);


	//std::vector<cv::VideoCapture> cameras = std::vector<cv::VideoCapture>(NUM_CAMERAS);

static CameraMap payload_frames;
	//CameraMap camera_model;
	std::future<CameraMap> cam_futures;

	/** @brief This method establishes the properties of each individual camera based on its initialization from initCamera() method
	@param camera we are receiving stream from (indicated as an integer value),
	which video capture object we are accessing, and the applications width and height
	@return No values are returned. This is mearly a test and can be useful later.
	**/
	bool initCamera(bool* x);// CameraMap* cam_map);// CameraMap& mat_data);// std::vector<std::vector<cv::Mat>>& mat_data);
	//bool initCamera(cv::Mat& mat_data);


	//void initCamera();// For internal purposes
};
