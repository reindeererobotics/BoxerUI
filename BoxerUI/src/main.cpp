// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
//#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
//#include <stdio.h>
//#include <sys/types.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utility.hpp>

#include <opencv2/imgproc/imgproc.hpp>
#include "BoxerUI_Controller.h"
#include "BoxerUI_Model.h"
#include "BoxerUI_View.h"
// #include "/home/username/opencv-master/include/opencv2/opencv.hpp"
// #include "/home/username/opencv-master/modules/highgui/include/opencv2/highgui/highgui.hpp"
// #include "/home/username/opencv-master/modules/core/include/opencv2/core/utility.hpp"

// #include "/home/username/opencv-master/modules/imgproc/include/opencv2/imgproc/imgproc.hpp"
// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h> // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h> // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h> // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
#include <glad/gl.h> // Initialize with gladLoadGL(...) or gladLoaderLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE	   // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h> // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE		 // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h> // Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char *description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void BindCVMat2GLTexture(cv::Mat &image, GLuint &imageTexture)
{
	if (image.empty())
	{
		std::cout << "image empty" << std::endl;
	}
	else
	{
		cv::cvtColor(image, image, cv::COLOR_BGR2RGBA);

		GLuint image_texture;
		glGenTextures(1, &imageTexture);
		glBindTexture(GL_TEXTURE_2D, imageTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Set texture clamping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_READ_COLOR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_READ_COLOR);

		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.ptr());
		glTexImage2D(GL_TEXTURE_2D,	   // Type of texture
					 0,				   // Pyramid level (for mip-mapping) - 0 is the top level
					 GL_RGB,		   // colour format to convert to
					 image.cols,	   // Image width
					 image.rows,	   // Image height
					 0,				   // Border width in pixels (can either be 1 or 0)
					 GL_RGBA,		   // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
					 GL_UNSIGNED_BYTE, // Image data type
					 image.data);	   // The actual image data itself

		//imageTexture = image_texture;
	}
}
void disp_frame(cv::Mat &frame, GLuint &my_frame_texture)
{
	cv::Mat frames_buf[5];
	for (int i = 0; i < 5; i++)
	{
		frames_buf[i] = frame;
		frame.~Mat();
	}
	for (int i = 0; i < 5; i++)
	{
		cv::Mat disp_frame = cv::Mat(100, 100, CV_64FC1);

		disp_frame = frames_buf[i];
		BindCVMat2GLTexture(disp_frame, my_frame_texture);
		ImGui::Text("pointer = %p", my_frame_texture);
		ImGui::Text("size = %d x %d", disp_frame.cols, disp_frame.rows);
		ImGui::Image((void *)(intptr_t)my_frame_texture, ImVec2((float)disp_frame.cols, (float)disp_frame.rows)); //reinterpret_cast<ImTextureID*>(my_frame_texture)
		disp_frame.release();
	}
}
int main(int, char **)
{
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

		// Decide GL+GLSL versions
#ifdef __APPLE__
	// GL 3.2 + GLSL 150
	const char *glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);		   // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char *glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	// Create window with graphics context
	int ui_window_width = 1280, ui_window_height = 720;
	GLFWwindow *window = glfwCreateWindow(ui_window_width, ui_window_height, "Reheindeer Robotics - BoxerUI", NULL, NULL);
	glfwGetWindowSize(window, &ui_window_width, &ui_window_height);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
	bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
	bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
	bool err = gladLoadGL(glfwGetProcAddress) == 0; // glad2 recommend using the windowing library loader instead of the (optionally) bundled one.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
	bool err = false;
	glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
	bool err = false;
	glbinding::initialize([](const char *name) { return (glbinding::ProcAddress)glfwGetProcAddress(name); });
#else
	bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	// Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = false;
	io.ConfigDockingWithShift = true;
	//io.ConfigDockingAlwaysTabBar = false;
	//io.ConfigViewportsNoTaskBarIcon = false;
	//io.ConfigViewportsNoDefaultParent = false;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle &style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

	// Our state
	//bool show_demo_window = true;
	bool show_index_window = true;
	bool show_boxer_windows = false;
	bool p_open = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//Initialize Boxer controller object.
	BoxerUI_Model boxerModel = BoxerUI_Model();
	BoxerUI_View boxerView;
	BoxerUI_Controller boxerController = BoxerUI_Controller(boxerView, boxerModel);
	//boxerController.payloadRecv();

	bool show_camera = false;
	int capture_camera = 0;
	cv::VideoCapture cap = cv::VideoCapture(capture_camera, cv::CAP_ANY);
	if (!cap.isOpened())
	{
		cout << "Camera not opened" << endl;
		return -1;
	}
	else
	{
		cout << "Camera opened at: " << capture_camera << endl;
	}
	cv::Mat frame;
	GLuint my_frame_texture;
	cout << cap.getBackendName() << endl;
	cout << cap.get(cv::CAP_PROP_POS_FRAMES) << endl;
	cap.set(3, ui_window_width / 3);  //frame width
	cap.set(4, ui_window_height / 3); //fram height

	//cap.set(cv::CAP_PROP_HW_ACCELERATION, cv::VIDEO_ACCELERATION_NONE);
	//cout << "FPS: "<<cap.get(cv::CAP_PROP_FPS)<<"\nAutoFocus: "<<cv::CAP_PROP_AUTOFOCUS << endl;
	//cap.get(cv::CAP_PROP_SETTINGS);
	//cap.set(cv::CAP_PROP_AUTO_EXPOSURE,cap.get(cv::CAP_PROP_BRIGHTNESS*15));
	//cout << cap.get(cv::CAP_PROP_FPS) << endl;

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//	ImGuiWindowClass *windowClass=new ImGuiWindowClass ;
		//(*windowClass).DockingAlwaysTabBar = true;
		//
		//ImGuiDockNodeFlags nodeFlags =  ImGuiDockNodeFlags_NoTabBar ;
		//windowClass->DockNodeFlagsOverrideSet = nodeFlags;
		////windowClass->DockingAlwaysTabBar = false;
		//SetNextWindowClass(windowClass);

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_NoCloseButton);
		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.

		{
			// if (show_index_window) {
			// 	//SetNextWindowSize(ImVec2(ui_window_width/4, ui_window_height/4), ImGuiCond_Always);
			// 	boxerController.displayIndexWindow( show_index_window);// , ui_window_width, ui_window_height);
			// }
			// else
			{
				//SetNextWindowViewport();
				boxerController.displayFPS();
				boxerController.demoWindows(); // show_demo_window);
				boxerController.updateBSView();
				boxerController.plotView();

				//if(cap.grab())
				{
					/*if (pid == 0)
					{*/
					ImGui::Begin("OpenGL/OpenCV Camera Test");
					//switch camera in drop down
						const char *list_cameras[] = {"0", "1"};
						static int item_current = 0;
						ImGui::Combo("List of Cameras", &item_current, list_cameras, IM_ARRAYSIZE(list_cameras));
						// capture_camera = item_current;
						//ImGui::SameLine(); 
						/*HelpMarker(
							"Refer to the \"Combo\" section below for an explanation of the full BeginCombo/EndCombo API, "
							"and demonstration of various flags.\n");*/
										   //TODO: place camera in process
					if (Button("Show Camera"))
					{
						show_camera = !show_camera;
						//TODO: Maybe putting the camera stream will improve performance & increase fps
						
					}
					if (show_camera)
					{
						
#ifdef _WIN32
						cap.retrieve(frame);
#else
						cap.read(frame);
						disp_frame(frame, my_frame_texture);
#endif
						// cv::Mat6
					}
					ImGui::End();
					//}
				}
				//else { cout << "Could not grab frame" << endl; }
			}
		}

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow *backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
