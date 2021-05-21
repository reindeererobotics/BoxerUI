#pragma once

#include "imgui.h"
#include "imgui_internal.h"
#include "implot.h"

//#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#define BUFFER_SIZE 5
#define NUM_CAMERAS 5  //5 is screenshot default. i.e. There are 5 cameras but 6 Mat frames so as the last mat frame is the screenshot
#define FREEZE_FRAME_IMG 5

//#include "TextTheme.h"



using namespace ImGui;
using namespace std;

class BoxerUI_View
{

	//ImGuiIO& io = ImGui::GetIO();
	//ImFont* default_font= io.Fonts->AddFontDefault();
	bool freeze_frame = false, enhance = false;
	cv::VideoCapture cameras[NUM_CAMERAS];// = {};//forward_capture, right_side_capture, left_side_capture, rear_capture;
	cv::Mat frames[NUM_CAMERAS+1];
	GLuint my_frame_texture;
private:
	static void dispFrame(cv::Mat* frame)
	{
		//creates a buffer of 5 frames before binding cv::Mat type to GLTexture
		cv::Mat frames_buf[BUFFER_SIZE];
		//GLuint my_frame_texture;
		for (int i = 0; i < BUFFER_SIZE; i++)
		{
			frames_buf[i] = *frame;
			(*frame).~Mat();
		}
		for (int i = 0; i < 5; i++)
		{
			cv::Mat disp_frame = cv::Mat(100, 100, CV_64FC1);

			disp_frame = frames_buf[i];
			BindCVMat2GLTexture(&disp_frame);// , & my_frame_texture);

			disp_frame.release();
		}

		/*BindCVMat2GLTexture(frame);
		frame->release();*/
	}

	static void BindCVMat2GLTexture(cv::Mat* disp_frame)//, GLuint* image_texture)
	{
		GLuint image_texture;
		if ((*disp_frame).empty())
		{
			std::cout << "image empty" << std::endl;
		}
		else
		{
			cv::cvtColor(*disp_frame, *disp_frame, cv::COLOR_BGR2RGBA);


			glGenTextures(1, &image_texture);
			glBindTexture(GL_TEXTURE_2D, image_texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Set texture clamping method
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_READ_COLOR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_READ_COLOR);

			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.ptr());
			glTexImage2D(GL_TEXTURE_2D,	   // Type of texture
				0,				   // Pyramid level (for mip-mapping) - 0 is the top level
				GL_RGB,		   // colour format to convert to
				(*disp_frame).cols,	   // Image width
				(*disp_frame).rows,	   // Image height
				0,				   // Border width in pixels (can either be 1 or 0)
				GL_RGBA,		   // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
				GL_UNSIGNED_BYTE, // Image data type
				(*disp_frame).data);	   // The actual image data itself
			ImGui::Text("pointer = %p", image_texture);
			ImGui::Text("size = %d x %d", (*disp_frame).cols, (*disp_frame).rows);
			ImGui::Image((void*)(intptr_t)image_texture, ImVec2((float)(*disp_frame).cols, (float)(*disp_frame).rows)); //reinterpret_cast<ImTextureID*>(my_frame_texture)
		}

	}
public:
	static void appFrameRate() {
		{ ImGui::Begin("Application Framerate");                          // Create a window called "Hello, world!" and append into it.
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End(); }
	}
	static void showdemos() {//bool show_demo_window) {

		bool show_another_window = false;
		bool show_demo_window = true;
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (&show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		{
			bool p_open = false;
			if (&show_demo_window)
			{
				ImPlot::CreateContext();
				ImPlot::ShowDemoWindow(&p_open);
				ImPlot::DestroyContext();
			}
		}
		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}
	}
	static void displaySensors(double temperature, double battery) {
		static int counter = 0;
		static bool setTempBttn = false;
		//ImFont* title_style{};
		//titleStyle(title_style);

		{
			ImGui::Begin("My Table Test");// , ImGuiWindowFlags_AlwaysAutoResize);

			{
				static ImGuiSelectableFlags selectFlags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiSelectableFlags_AllowDoubleClick;
				ImGui::BeginTable("table", 2);


				//static char *tableHeader[] = { "Sensors","Current","Max","Min" };
				//static char* sensors[] = { "Temperature","Battery","Tires","Min", "Min" };
				//titleStyle();
				TableSetupColumn("Sensors", ImGuiTableColumnFlags_WidthStretch);
				TableSetupColumn("Values", ImGuiTableColumnFlags_WidthStretch);
				TableHeadersRow();
				TableNextRow();
				TableNextColumn();
				//ImGui::PushFont(title_style);
				Text("Temperature");
				//ImGui::PopFont();
				//ImGui::PushFont(default_font);
				TableNextColumn(); Text("%f", temperature);
				TableNextRow();
				TableNextColumn(); Text("Battery"); TableNextColumn();
				Text("%f", battery);

				ImGui::EndTable(); }

			if (Button("change temperature")) {
				//boxerController.setModelTemperature(19.3);
				setTempBttn = true;
				//pid = CreateProcess();
			}
			if (setTempBttn) {
				ImGui::SameLine();
				ImGui::Text("Thanks for clicking me! Counter: %d", counter);
			}
			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);
			ImGuiListClipper clipper;
			clipper.Begin(10);         // We have 1000 elements, evenly spaced.               
			while (clipper.Step())
				for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) {
					ImGui::Text("line number %d", i);
				}

			ImGui::End();
		}
	}
	static void plotStream() {

		bool show_imgui_style_editor = false;
		//int   bar_data_A[11] = {3,11,1,5,6,1,1,9,7 };
		//int   bar_data_B[11] = {0, 1,2,3,4,5,6,7,8,9,10 };


		float xs1[1001], ys1[1001];
		for (int i = 0; i < 1001; ++i) {
			xs1[i] = i * 0.001f;
			ys1[i] = 0.5f + 0.5f * sinf(50 * (xs1[i] + (float)ImGui::GetTime() / 10));
		}
		static float xs2[11], ys2[11];
		for (int i = 0; i < 11; ++i) {
			xs2[i] = i * 0.1f;
			ys2[i] = xs2[i] * xs2[i];
		}

		ImPlot::CreateContext();
		ImGui::Begin("ImPlot Test", &show_imgui_style_editor);


		if (ImPlot::BeginPlot("My Plot", "my x label", "my y label")) {

			//ImPlot::PlotBars("My Bar Plot", bar_data, 11);
			ImPlot::PlotLine("My Line Plot1", xs1, ys1, 1001);
			ImPlot::SetNextMarkerStyle(ImPlotMarker_Diamond);
			ImPlot::PlotLine("My Line Plot2", xs2, ys2, 11);
			ImPlot::EndPlot();
		}

		ImGui::End();
		ImPlot::DestroyContext();
	}
	static void indexwindow(bool& boxer_analytics) {//, int ui_window_width, int ui_window_height) {
		bool p_open = true;
		ImGuiWindowFlags indexFlags = ImGuiWindowFlags_NoSavedSettings;
		//ImGuiWindowClass* windowClass = new ImGuiWindowClass;
		//ImGuiDockNodeFlags nodeFlags = ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_CentralNode ;
		//windowClass->DockNodeFlagsOverrideSet = nodeFlags;
		//(*windowClass).DockingAlwaysTabBar = false;
		//windowClass->DockingAllowUnclassed=true;
		//SetNextWindowClass(windowClass);

		/*ImGuiWindow *index_window=NULL;
		ImGuiID nodeID=index_window->GetID("Index");
		DockBuilderGetCentralNode(nodeID);
		SetWindowDock(index_window, nodeID,ImGuiCond_FirstUseEver);*/

		////GetWindowWidth();
		////ImGuiWindow* indexWindow;
		//index_window->GetID("index");
		//BeginDocked(index_window, &p_open);


		static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
		// We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
		// Based on your use case you may want one of the other.
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);

		Begin("Index", &p_open, flags);//, indexFlags);
		Text("Boxr");
		if (Button("Open boxer analytics", ImVec2(200, 100))) {
			boxer_analytics = false;
			cout << boxer_analytics << endl;
		}
		End();

		//WindowClass
		//return boxer_analytics;
	}

	static void sideNav() {
		ImGui::Begin("Settings");
		//See FAQ regarding ID for swapping items. Keyboard
		//ImFont* font1 = io.Fonts->AddFontFromFileTTF("font.ttf", size_pixels);
		Text("SOme setting", 1, 1, 1);

		ImGui::End();
	}


	static void settings() {//settings that will replace the sideNav upon toggle
		ImGui::Begin("Settings");
		//See FAQ regarding ID for swapping items. Keyboard
		//ImFont* font1 = io.Fonts->AddFontFromFileTTF("font.ttf", size_pixels);
		Text("SOme setting", 1, 1, 1);

		ImGui::End();
	}

	void initCamera(bool* show_camera, float* w, float* h) {
		if (show_camera)
		{
			float capture_width, capture_height;
			for (int i = 0; i < NUM_CAMERAS; i++)
			{
				int temp_size = (ImGui::GetCurrentWindow()->ContentSize.x);
				//set and initialize the cameras
				//If index is 1, set the width & hwight to half its passed value. Else set it to a third of its value
				capture_width = (*w) / (i == 0 ? temp_size : 5);
				capture_height = (*h) / (i == 0 ? temp_size : 5);

				//set the camera properties
				setCameraProp(&i, &cameras[i], (&capture_width), (&capture_height));
			}
		}
		else
		{
			for (int i = 0; i < NUM_CAMERAS; i++)
			{
				destroyCamera(&i);
			}
		}
	}

	//destroy the frame & cap objects then release from memory
	void destroyCamera(int* index) {
		cameras[*index].~VideoCapture();
		frames[*index].~Mat();
	}


	void setCameraProp(int* camera, cv::VideoCapture* capture, float* w, float* h) { //This method establishes the properties of each individual camera based on its initialization from initCamera() method
		//change param of line below from 0 to *camera
		*(capture) = cv::VideoCapture(*camera == 0 ? 1 : 0, cv::CAP_ANY);
		if (!(*capture).isOpened())
		{
			cout << "Camera not opened" << endl;
		}
		else
		{
			cout << "Camera opened at: " << 0 << endl;
			cout << (*capture).getBackendName() << endl;
			cout << (*capture).get(cv::CAP_PROP_POS_FRAMES) << endl;
			(*capture).set(3, *w);  //frame width
			(*capture).set(4, *h); //fram height
		}
	}


	void streamCamera(int* camera) {//cv::VideoCapture* cap,cv::Mat* frame) {//stream the data and bind to unique Mat objects

		if (Button("Freeze Frame")) {//if freeze frame is clicked. capture the current frame...
			freeze_frame = !freeze_frame;
			//if (freeze_frame)
			cameras[*camera].read(frames[FREEZE_FRAME_IMG]);

		}
		//if (freeze_frame) { freezeFrame(); }
		// else { destroyCamera(FREEZE_FRAME_IMG); }

		//if (*camera == 0)
		{
			ImGui::BeginChild("Main_Viewport", ImVec2((ImGui::GetCurrentWindow()->ContentSize.x) * 0.75f, 0.0f), true);
			//camera == 0 ?
			freeze_frame?freezeFrame():setCamContext(*camera);
			//: setCamContext(*camera);
			ImGui::EndChild();
			ImGui::SameLine();
		}

		ImGui::BeginChild("childCams", ImVec2(0.0f, 0.0f), true);
		for (int i = 0; i < NUM_CAMERAS; i++)
		{
			if ((*camera) == i) {//i.e. if the current index camera is in context, skip it in iteration and set its context to secondary in the side queue 
				continue;
			}
			else { setCamContext(i); }//TODO set the cameras prop so current context stream is appropriatly sized
		}
		ImGui::EndChild();

	}

	void setCamContext(int context = 0) {

#ifdef _WIN32
		//context==0?setCameraProp(context, cameras[context],)
		cameras[context].retrieve(frames[context]);
#else
		cameras[context].read(frames[context]);
#endif

		dispFrame(&frames[context]);
	}

	void freezeFrame() {
		//if (freeze_frame)
		//{
			//... and render onto screen through similar process as streaming as video
		cout << "Freeze frame: " << freeze_frame << endl;
		//cv::Mat freeze_frame_img;
		//freeze_frame_img=frame.clone();
		BindCVMat2GLTexture(&frames[FREEZE_FRAME_IMG]);// , & frame_texture);
		static int  zoom_vert, zoom_hor = 0, zoom = 3;
		if (Button("Enhance")) {
			//TODO: resize the image & sharpen to increase quality upon zoom
			//cv::resize(freeze_frame_img, freeze_frame_img, cv::Size(), 0.5, 0.5, cv::INTER_LINEAR);
			enhance = !enhance;
		}
		if (enhance) {//TODO: Enhance image. i.e impl zooming into image without loosing image quality
			//ImGui::VSliderInt("Vertical", ImVec2(18, 160), &zoom_vert, 1, 5);
			//ImGui::SliderInt("Horizontal", &zoom_hor, 1, 5);
			//ImGui::SliderInt("Zoom", &zoom, 1, 5);
			//for (int i = 0; i < zoom_val; i++)
				//ImGui::Text("%*sThis is line %d", i * 4, "", i);
			//cv::Rect2d roi = //(zoom_vert, zoom_vert, freeze_frame_img.cols/2, freeze_frame_img.rows/2);

			//freeze_frame_img = freeze_frame_img(cv::selectROI(freeze_frame_img, false, false));
		}
		//}
	}


	void swapCamViews() {//TODO: Resume later. This is to allow the dragging and dropping of cam views on the UI to swap them out

		for (int n = 0; n < IM_ARRAYSIZE(cameras); n++)
		{
			ImGui::PushID(n);
			if (n != 0)
				ImGui::SameLine();
			//ImGui::Button(viewCameras[n], ImVec2(60, 60));
			//streamCamera(&cameras[n],&frames[n]);


			// Our buttons are both drag sources and drag targets here!
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				// Set payload to carry the index of our item (could be anything)
				ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(cv::VideoCapture));

				// Display preview (could be anything, e.g. when dragging an image we could decide to display
				// the filename and a small preview of the image, etc.)
				//if (mode == Mode_Copy) { ImGui::Text("Copy %s", names[n]); }
				//if (mode == Mode_Move) { ImGui::Text("Move %s", names[n]); }
				//if (mode == Mode_Swap) { ImGui::Text("Swap %s", names[n]); }

				//n == 0 ? cameraContext() :

				ImGui::EndDragDropSource();
			}
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
				{
					IM_ASSERT(payload->DataSize == sizeof(int));
					int payload_n = *(const int*)payload->Data;

					//Swap the camera streams
					const cv::VideoCapture tmp = cameras[n];
					cameras[n] = cameras[payload_n];
					cameras[payload_n] = tmp;

				}
				ImGui::EndDragDropTarget();
			}
			ImGui::PopID();
		}

	}

};
