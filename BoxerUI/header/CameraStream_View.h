#pragma once
#include "Boxer.h"
#include <BoxerUI_View.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp> //Note: no need to include these headers in the working file. These will be handled automatically by linker

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#ifdef _WIN32

#else
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#endif

//#ifndef CAMERASTREAM_VIEW_H_
//...
//#endif // !CAMERASTREAM_VIEW_H_
//Preprocessor. Checks if the symbol has been not bee ndefined. Use #pragma, it includes the symbol once

#define BUFFER_SIZE 5
#define NUM_CAMERAS 4
#define FREEZE_FRAME_IMG 5

class CameraStream: public BoxerUI_View// public BoxerUI_Controller
{
	bool freeze_frame = false, enhance = false;
	cv::VideoCapture cameras[NUM_CAMERAS];
	cv::Mat frames[NUM_CAMERAS + 1]; //Last frame in array is dedicated to store freeze frame
	uchar frames_data[NUM_CAMERAS + 1]; //Last frame in array is dedicated to store freeze frame

#if _WIN32
#else 
pid_t pid;
#endif // !_WIN32
	
	
private:
	void dispFrame(cv::Mat *frame);

	void BindCVMat2GLTexture(cv::Mat *disp_frame);

	//destroy the frame & cap objects then release from memory
	void destroyCamera(int *index);

	void setCameraPropTest(int *camera, cv::VideoCapture *capture, float *w, float *h);

	//for internal testing only
	//void setCamContext(int context);
	
	void streamCamera(int* camera);
	
	void freezeFrame();

	void swapCamViews();
public:
	void setCamContext(int context);
	void initCamera(uchar mat_data);
	void initCamera();// For internal purposes
};
