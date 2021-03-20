#pragma once

#include "imgui.h"
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

        static char* tableHeader[] = { "Sensors","Current","Max","Min" };
        static char* sensors[] = { "Temperature","Battery","Tires","Min", "Min" };

        TableSetupColumn("Sensors", ImGuiTableColumnFlags_WidthStretch);
        TableSetupColumn("Values", ImGuiTableColumnFlags_WidthStretch);
        TableHeadersRow();
        TableNextRow();
        TableNextColumn();
        Text("Temperature");
        TableNextColumn();Text("%f", temperature);
        TableNextRow();
        TableNextColumn();Text("Battery");TableNextColumn();
        
        Text("%f", battery);
        
        //for each (char* header in tableHeader)
        //{
        //    TableSetupColumn(header, ImGuiTableColumnFlags_WidthStretch);

        //}
        //TableHeadersRow();
        //for (int row = 0; row < 5; row++)
        //{
        //    ImGui::TableNextRow();
        //    for (int column = 0; column < 4; column++)
        //    {
        //        ImGui::TableSetColumnIndex(column);
        //        ImGui::Text("%s %d,%d", (column >= 3) ? "Stretch" : "Fixed", column, row);
        //        if (ImGui::TableGetColumnIndex() == 0)
        //            Button(sensors[row]);
        //        //ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 100, 0, 255));
        //    }
        //}
        ImGui::EndTable();
	}
    static void cameraStream() {
        bool p_open = false;
        Begin("Canvas Test", &p_open);
        ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
        ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
        if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
        if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
        ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

        // Draw border and background color
        ImGuiIO& io = ImGui::GetIO();
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        //draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
        //draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));

       /* {cv::VideoCapture cap(0);
        if (!cap.isOpened()) {
            cout << "Change camera port number";

        }
        while (true)
        {
            cv::Mat frame;
            cap.read(frame);
            cv::imshow("Camera", frame);
            if (cv::waitKey(30) == 27) {
                cout << "Something Happened I Guess";
            }
        }
        }*/

        
        End();
    }
};