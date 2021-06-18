#pragma once
#include "Boxer.h"
#include "CustomComponents_View.h"
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

class CameraStream
{
	bool freeze_frame = false, enhance = false;
	cv::VideoCapture cameras[NUM_CAMERAS];
	cv::Mat frames[NUM_CAMERAS + 1]; //Last frame in array is dedicated to store freeze frame
	pid_t pid;
private:
	void dispFrame(cv::Mat *frame);

	void BindCVMat2GLTexture(cv::Mat *disp_frame);
	void initCamera(bool *show_camera, float *w, float *h);// For internal purposes

	//destroy the frame & cap objects then release from memory
	void destroyCamera(int *index);

	void setCameraPropTest(int *camera, cv::VideoCapture *capture, float *w, float *h);

	void streamCamera(int *camera);

	void setCamContext(int context);

	void freezeFrame();

	void swapCamViews();

public:
	void initCamera();
};
