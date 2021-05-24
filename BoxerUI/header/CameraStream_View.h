#pragma once


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
//#define BUFFER_SIZE 5
//#define NUM_CAMERAS 4
//#define FREEZE_FRAME_IMG 5

class CameraStream
{bool freeze_frame = false, enhance = false;
	cv::VideoCapture cameras[5];
	cv::Mat frames[5 + 1];
	//GLuint my_frame_texture;
private:
	
	void dispFrame(cv::Mat* frame);

	void BindCVMat2GLTexture(cv::Mat* disp_frame);

public:
	void initCamera(bool show_camera, float w, float h);

	//destroy the frame & cap objects then release from memory
	void destroyCamera(int* index) {};

	void setCameraProp(int* camera, cv::VideoCapture* capture, float* w, float* h);

	void streamCamera(int* camera) {};

	void setCamContext(int context = 0);

	void freezeFrame();

	void swapCamViews();
};
