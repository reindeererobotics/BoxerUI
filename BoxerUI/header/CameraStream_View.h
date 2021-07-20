#pragma once
#include "Boxer.h"
#include "Inputs.h"
#include "BoxerUI_View.h"
#include "CustomComponents_View.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>//Note: no need to include these headers in the working file. These will be handled automatically by linker

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>


//#ifndef CAMERASTREAM_VIEW_H_
//...
//#endif // !CAMERASTREAM_VIEW_H_
//Don't use above. Its legacy & checks if the header has been included/defined before it includes it in file. Use pragma instead(Line 1). 

//class MyClass
//{
//public:
//	MyClass();
//	~MyClass();
//
//private:
//
//};
//
//MyClass::MyClass()
//{
//}
//
//MyClass::~MyClass()
//{
//}
#define BUFFER_SIZE 5
#define NUM_CAMERAS 4
#define FREEZE_FRAME_IMG 5


class CameraStream: public BoxerUI_View
{
	bool freeze_frame = false, enhance = false;
	cv::VideoCapture cameras[NUM_CAMERAS];
	cv::Mat frames[NUM_CAMERAS + 1];//Last frame in array is dedicated to store freeze frame
private:

	void dispFrame(cv::Mat* frame);

	void BindCVMat2GLTexture(cv::Mat* disp_frame);

public:
	void initCamera(bool* show_camera, float* w, float* h);

	//destroy the frame & cap objects then release from memory
	void destroyCamera(int* index);

	void setCameraPropTest(int* camera, cv::VideoCapture* capture, float* w, float* h);

	void streamCamera(int* camera);

	void setCamContext(int context);

	void freezeFrame();

	void swapCamViews();
};
