#pragma once

#include "imgui.h"
#include "implot/implot.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace ImGui;
using namespace std;


class BoxerUI_View
{
public:
	static void displaySensors(double temperature, double battery) {

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

		ImGui::EndTable();
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
};