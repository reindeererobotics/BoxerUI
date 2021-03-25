#pragma once

#include "imgui.h"
#include "imgui_internal.h"
#include "implot.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace ImGui;
using namespace std;

class BoxerUI_View
{
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
		{
			ImGui::Begin("My Table Test");// , ImGuiWindowFlags_AlwaysAutoResize);

			{
				static ImGuiSelectableFlags selectFlags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiSelectableFlags_AllowDoubleClick;
				ImGui::BeginTable("table", 2);

				//static char *tableHeader[] = { "Sensors","Current","Max","Min" };
				//static char* sensors[] = { "Temperature","Battery","Tires","Min", "Min" };

				TableSetupColumn("Sensors", ImGuiTableColumnFlags_WidthStretch);
				TableSetupColumn("Values", ImGuiTableColumnFlags_WidthStretch);
				TableHeadersRow();
				TableNextRow();
				TableNextColumn();
				Text("Temperature");
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
	static void cameraStream() {

	}
	static void indexwindow(bool& boxer_analytics) {//, int ui_window_width, int ui_window_height) {
		bool p_open = true;
		ImGuiWindowFlags indexFlags =  ImGuiWindowFlags_NoSavedSettings;
		ImGuiWindowClass* windowClass = new ImGuiWindowClass;
		ImGuiDockNodeFlags nodeFlags = ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_CentralNode ;
		windowClass->DockNodeFlagsOverrideSet = nodeFlags;
		//(*windowClass).DockingAlwaysTabBar = false;
		//windowClass->DockingAllowUnclassed=true;
		SetNextWindowClass(windowClass);

		
		/*ImGuiWindow *index_window=NULL;
		ImGuiID nodeID=index_window->GetID("Index");
		DockBuilderGetCentralNode(nodeID);
		SetWindowDock(index_window, nodeID,ImGuiCond_FirstUseEver);*/

		////GetWindowWidth();
		////ImGuiWindow* indexWindow;
		//index_window->GetID("index");
		//BeginDocked(index_window, &p_open);

		Begin("Index", &p_open , indexFlags);
		Text("Boxr");
		if (Button("Open boxer analytics", ImVec2(200, 100))) {
			boxer_analytics = false;
			cout << boxer_analytics << endl;
		}
		End();

		//WindowClass
		//return boxer_analytics;
	}
};