#include "CameraStream_View.h"

void CameraStream::dispFrame(cv::Mat* frame)
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
		BindCVMat2GLTexture(&disp_frame); // , & my_frame_texture);

		disp_frame.release();
	}
}

void CameraStream::BindCVMat2GLTexture(cv::Mat* disp_frame) //, GLuint* image_texture)
{
	ImGuiIO& io = ImGui::GetIO();
	GLuint image_texture;
	if ((*disp_frame).empty())
	{
		std::cout << "image empty" << std::endl;
	}
	else
	{
		cv::Mat x = cv::Mat(100, 100, CV_32FC2);
		cv::cvtColor(*disp_frame, *disp_frame, cv::COLOR_BGR2RGBA);

		glGenTextures(1, &image_texture);
		glBindTexture(GL_TEXTURE_2D, image_texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Set texture clamping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_READ_COLOR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_READ_COLOR);

		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.ptr());
		glTexImage2D(GL_TEXTURE_2D,		  // Type of texture
			0,					  // Pyramid level (for mip-mapping) - 0 is the top level
			GL_RGB,			  // colour format to convert to
			(*disp_frame).cols,  // Image width
			(*disp_frame).rows,  // Image height
			0,					  // Border width in pixels (can either be 1 or 0)
			GL_RGBA,			  // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
			GL_UNSIGNED_BYTE,	  // Image data type
			(*disp_frame).data); // The actual image data itself
		ImGui::Text("pointer = %p", image_texture);
		ImGui::Text("size = %d x %d", (*disp_frame).cols, (*disp_frame).rows);

		ImTextureID my_tex_id = (void*)(intptr_t)image_texture;
		float my_tex_w = (float)io.Fonts->TexWidth;
		float my_tex_h = (float)io.Fonts->TexHeight;
		{
			ImGui::Text("%.0fx%.0f", (*disp_frame).cols, (float)(*disp_frame).rows);
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImVec2 uv_min = ImVec2(0.0f, 0.0f);																							 // Top-left
			ImVec2 uv_max = ImVec2(1.0f, 1.0f);																							 // Lower-right
			ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);																			 // No tint
			ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);																			 // 50% opaque white
			ImGui::Image(my_tex_id, ImVec2((float)(*disp_frame).cols, (float)(*disp_frame).rows), uv_min, uv_max, tint_col, border_col); //reinterpret_cast<ImTextureID*>(my_frame_texture)

			//ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), uv_min, uv_max, tint_col, border_col);
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				float region_sz = 32.0f;
				float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
				float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
				float zoom = 4.0f;
				if (region_x < 0.0f)
				{
					region_x = 0.0f;
				}
				else if (region_x > (*disp_frame).cols - region_sz)
				{
					region_x = (*disp_frame).cols - region_sz;
				}
				if (region_y < 0.0f)
				{
					region_y = 0.0f;
				}
				else if (region_y > (float)(*disp_frame).rows - region_sz)
				{
					region_y = (float)(*disp_frame).rows - region_sz;
				}
				ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
				ImGui::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
				ImVec2 uv0 = ImVec2((region_x) / (*disp_frame).cols, (region_y) / (float)(*disp_frame).rows);
				ImVec2 uv1 = ImVec2((region_x + region_sz) / (*disp_frame).cols, (region_y + region_sz) / (float)(*disp_frame).rows);
				ImGui::Image(my_tex_id, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tint_col, border_col);
				ImGui::EndTooltip();
			}
		}
	}
}

/** @brief This method establishes the properties of each individual camera based on its initialization from initCamera() method

@param camera we are receiving stream from (indicated as an integer value),
which video capture object we are accessing, and the applications width and height
@return No values are returned. This is mearly a test and can be useful later.
**/
void CameraStream::initCamera()
{
	static bool show_camera = false;//, cam_stream_process = true;
	static int item_current = 0;

	ImGui::Begin("OpenGL/OpenCV Camera Test###camstream");

	//printf("Child process starts with PID = %d\n", (int)getpid());
	if (ImGui::Button("Show Camera"))
	{
		show_camera = !show_camera;
	}
	if (show_camera)
	{
		//if ((pid = fork()) < 0)
		{
			//It may fail -- super rare
			perror("Fork failed");
			//return EXIT_FAILURE;
		}
		//else if (pid > 0)
		{
			//If it returns a positive number, you're in the parent process and pid holds the pid of the child

			//printf("Boxer Main process id: %d\n", getpid());
			//printf("Camera process pid in mainis %d\n", pid);
		}
		//else
		{
			//Camera stream process
			//printf("Camera process id: %d\n", getpid()); //Child process

			float capture_width, capture_height;
			for (int i = 0; i < NUM_CAMERAS; i++)
			{
				float temp_size = (ImGui::GetCurrentWindow()->ContentSize.x);
				//set and initialize the cameras
				//If index is 1, set the width & hwight to half its passed value. Else set it to a third of its value
				capture_width = (ImGui::GetCurrentWindow()->ContentSize.x) / (i == 0 ? temp_size : 5);
				capture_height = (ImGui::GetCurrentWindow()->ContentSize.y) / (i == 0 ? temp_size : 5);

				//set the camera properties
				//TODO change "i==0?1:0" --> i==0?*camera:0
				cameras[i] = cv::VideoCapture(i == 0 ? 1 : 0, cv::CAP_ANY);
				setCameraPropTest(&i, &cameras[i], (&capture_width), (&capture_height));
			}

			//switch camera in drop down
			const char* list_cameras[] = { "1", "2", "3", "4" };

			if (ImGui::Combo("List of Cameras", &item_current, list_cameras, IM_ARRAYSIZE(list_cameras)))
			{
				// if current item changes in the dropdown. the main context stream is swapped with the item_current stream in the queue

				std::cout << "item_current: " << item_current << std::endl;
			}
			// capture_camera = item_current;
			ImGui::SameLine();
			HelpMarker(
				"Refer to the \"Combo\" section below for an explanation of the full BeginCombo/EndCombo API, "
				"and demonstration of various flags.\n");

			// if (show_camera)
			{
				streamCamera(&item_current);
			}
		}
	}
	/*else if (show_camera)
	{
		kill(pid,SIGTSTP);
	}*/
	else
	{
		for (int i = 0; i < NUM_CAMERAS; i++)
		{
			destroyCamera(&i);
		}
	}

	ImGui::End();
	//ImGui::NewFrame();
}

void CameraStream::destroyCamera(int* index)
{
	frames[*index].~Mat();
	// return;

	//for internal testing purposes only
	cameras[*index].~VideoCapture();
}

void CameraStream::setCameraPropTest(int* camera, cv::VideoCapture* capture, float* w, float* h)
{
	//This method establishes the properties of each individual camera based on its initialization from initCamera() method
	if (!(*capture).isOpened())
	{
		std::cout << "Camera not opened" << std::endl;

	}
	else
	{
		std::cout << "Camera opened at: " << 0 << std::endl;
		std::cout << (*capture).getBackendName() << std::endl;
		std::cout << (*capture).get(cv::CAP_PROP_POS_FRAMES) << std::endl;
		(*capture).set(3, *w); //frame width
		(*capture).set(4, *h); //fram height
	}
}

void CameraStream::streamCamera(int* camera)
{ //cv::VideoCapture* cap,cv::Mat* frame) {//stream the data and bind to unique Mat objects

	if (ImGui::Button("Freeze Frame"))
	{ //if freeze frame is clicked. capture the current frame...
		freeze_frame = !freeze_frame;

		//TODO: clone the main context frame to freeze frame then display
		//cameras[*camera].retrieve(frames[FREEZE_FRAME_IMG]);
	}


	{//Main "viewport"/context stream
		ImGui::BeginChild("Main_Viewport", ImVec2((ImGui::GetCurrentWindow()->ContentSize.x) * 0.75f, 0.0f), true);
		freeze_frame ? freezeFrame() : setCamContext(*camera);
		ImGui::EndChild();
		ImGui::SameLine();
	}

	{ //Queue of streams on side child window
		ImGui::BeginChild("childCams", ImVec2(0.0f, 0.0f), true);
		for (int i = 0; i < NUM_CAMERAS; i++)
		{
			if ((*camera) == i)
			{ //i.e. if the current index camera is in context, skip it in iteration and set its context to secondary in the side queue
				continue;
			}
			else
			{
				setCamContext(i);
			} //TODO set the cameras prop so current context stream is appropriatly sized
		}
		ImGui::EndChild();
	}
}

void CameraStream::setCamContext(int context = 0)
{
	//*CameraStream::frames[context].data=CameraStream::frames_data[context];

#ifdef _WIN32
	//context==0?setCameraProp(context, cameras[context],)
	cameras[context].retrieve(frames[context]);
#else
	cameras[context].read(frames[context]);
#endif
	dispFrame(&frames[context]);

}

void CameraStream::freezeFrame()
{
	std::cout << "Freeze frame: " << freeze_frame << std::endl;
	//cv::Mat freeze_frame_img;
	//freeze_frame_img=frame.clone();
	BindCVMat2GLTexture(&frames[FREEZE_FRAME_IMG]); // , & frame_texture);
	static int zoom_vert, zoom_hor = 0, zoom = 3;
	if (ImGui::Button("Enhance"))
	{
		//TODO: resize the image & sharpen to increase quality upon zoom
		//cv::resize(freeze_frame_img, freeze_frame_img, cv::Size(), 0.5, 0.5, cv::INTER_LINEAR);
		enhance = !enhance;
	}
	if (enhance)
	{	//TODO: Enhance image. i.e impl zooming into image without loosing image quality
		//ImGui::VSliderInt("Vertical", ImVec2(18, 160), &zoom_vert, 1, 5);
		//ImGui::SliderInt("Horizontal", &zoom_hor, 1, 5);
		//ImGui::SliderInt("Zoom", &zoom, 1, 5);
		//for (int i = 0; i < zoom_val; i++)
		//ImGui::Text("%*sThis is line %d", i * 4, "", i);
		//cv::Rect2d roi = //(zoom_vert, zoom_vert, freeze_frame_img.cols/2, freeze_frame_img.rows/2);

		//freeze_frame_img = freeze_frame_img(cv::selectROI(freeze_frame_img, false, false));
	}
}

void CameraStream::swapCamViews()
{ //TODO: Resume later. This is to allow the dragging and dropping of cam views on the UI to swap them out

	for (int n = 0; n < IM_ARRAYSIZE(cameras); n++)
	{
		ImGui::PushID(n);
		if (n != 0)
			ImGui::SameLine();
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

bool CameraStream::initCamera(cv::Mat mat_data)
{
	//, cam_stream_process = true;
	static int item_current = 0;

	{
		ImGui::Begin("OpenGL/OpenCV Camera Test###camstream");

		if (ImGui::Button("Show Camera"))
			show_camera = !show_camera;

		if (show_camera)
		{
			//if ((pid = fork()) < 0)
			{
				//It may fail -- super rare
				perror("Fork failed");
				//return EXIT_FAILURE;
			}
			//else if (pid > 0)
			{
				//If it returns a positive number, you're in the parent process and pid holds the pid of the child

				//printf("Boxer Main process id: %d\n", getpid());
				//printf("Camera process pid in mainis %d\n", pid);
			}
			//else
			{
				//Camera stream process
				//printf("Camera process id: %d\n", getpid()); //Child process
				//initCamera(&show_camera, &ImGui::GetCurrentWindow()->ContentSize.x, &ImGui::GetCurrentWindow()->ContentSize.y);

				//switch camera in drop down
				const char* list_cameras[] = { "1", "2", "3", "4" };

				if (ImGui::Combo("List of Cameras", &item_current, list_cameras, IM_ARRAYSIZE(list_cameras)))
				{
					// if current item changes in the dropdown. the main context stream is swapped with the item_current stream in the queue
					//boxerController.destroyCameraView(&item_current); //if the camera is currently streaming
					//show_camera = true;
					std::cout << "item_current: " << item_current << std::endl;
				}
				// capture_camera = item_current;
				ImGui::SameLine();
				HelpMarker(
					"Refer to the \"Combo\" section below for an explanation of the full BeginCombo/EndCombo API, "
					"and demonstration of various flags.\n");

				// if (show_camera)
				{
					//TODO Create thread here to process streaming content to window
					{
						*frames = mat_data;
						streamCamera(&item_current);
					}
				}
			}
		}
		/*else if (show_camera)
		{
			kill(pid,SIGTSTP);
		}*/


		ImGui::End();
	}

	//return EXIT_SUCCESS;
	return show_camera;
}




