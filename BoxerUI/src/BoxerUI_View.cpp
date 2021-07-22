#include "BoxerUI_View.h"


#include <iostream>

#include "TextTheme.h"
#include "resource/icons/IconFontCppHeaders/IconsFontAwesome5Brands.h"
#include "resource/icons/IconFontCppHeaders/IconsMaterialDesign.h"

using namespace ImGui;
using namespace std;


void BoxerUI_View::appFrameRate() {
	{ ImGui::Begin("Application Framerate");                          // Create a window called "Hello, world!" and append into it.
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End(); }
}
void BoxerUI_View::showdemos() {//bool show_demo_window) {

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
void BoxerUI_View::displaySensors(double temperature, double battery) {
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
void BoxerUI_View::plotStream() {

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
void BoxerUI_View::indexwindow(bool* boxer_analytics) {//, int ui_window_width, int ui_window_height) {
	bool p_open = true;

	static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);

	ImGui::SetNextWindowViewport(viewport->ID);
	//ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	//ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	const ImVec2 x = ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);


	//ImGui::SetWindowPos(ImVec2(GetCurrentWindow()->Pos.x,GetCurrentWindow()->Pos.y));

	//const ImVec2 pos = ImVec2(ImGui::GetCurrentWindow()->ContentSize.x *0.5, ImGui::GetCurrentWindow()->ContentSize.y*0.5);
	//ImGui::GetMainViewport()->Pos.x;
	//ImGui::GetMainViewport()->Size.x;
	//ImGui::GetWindowSize()->Size.x;
	//ImGui::GetWindowViewPort()->Size.x;
	//cout << ImGui::GetCurrentWindow()->Size.x << endl << ImGui::GetCurrentWindow()->Size.y;


	Begin("Index", &p_open, flags);//, indexFlags);
	const ImVec2 pos = ImVec2(viewport->WorkPos.x + (viewport->WorkSize.x * 0.15), viewport->WorkPos.y + (viewport->WorkSize.y * 0.15));
	ImGui::SetNextWindowPos(pos);// pos);
	//ImGui::SetNextWindowPos);
	//ImGui::SetNextWindowPos(x, ImGuiCond_FirstUseEver);
	//ImGui::SameLine(ImGui::GetWindowWidth() / 2);
	ImGui::BeginChild("identification", ImVec2(0.0f, 0.0f), false);// , ImGuiWindowFlags_AlwaysAutoResize);

	PushFont(ImGui::GetFont()->ContainerAtlas->Fonts[1]);
	Text("Boxr");
	PopFont();

	ImGuiInputTextFlags signin_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_NoUndoRedo;
	static char username[64], password[64];
	ImGui::InputTextWithHint("Username", "Username", username, IM_ARRAYSIZE(username), signin_flags);
	ImGui::SameLine(); HelpMarker("Enter your credentials here");
	//cout << IsItemEdited() ? "True" : "False";
	ImGui::InputTextWithHint("Password", "Password", password, IM_ARRAYSIZE(password), signin_flags |= ImGuiInputTextFlags_Password);
	//ImGui::InputText("password (clear)", password, IM_ARRAYSIZE(password));

	Spacing();
	if (Button("Login", ImVec2(65, 30))) {
		*boxer_analytics = false;
		cout << *boxer_analytics << endl;
	}
	SameLine(185);
	//Indent(80.0f);
	if (Button("Register", ImVec2(65, 30))) {
		//*boxer_analytics = false;
		cout << *boxer_analytics << endl;
	}
	EndChild();
	End();
}

bool BoxerUI_View::sideNav() {
	static bool toggle_settings = false;

	//ImGui::EndFrame();
	//ImGui::Render();
	//if (ImGuiConfigFlags_ViewportsEnable) {
	//ImGui::UpdatePlatformWindows();
	
	//ImGui::RenderPlatformWindowsDefault();
	//}
	//ImGui::NewFrame();

	ImGui::Begin("##sideNav");
	//See FAQ regarding ID for swapping items. Keyboard
	//ImFont* font1 = io.Fonts->AddFontFromFileTTF("font.ttf", size_pixels);



	{
		//Settings
		if (ImGui::Button(ICON_MD_SETTINGS "##settings")) { toggle_settings = !toggle_settings; }
		if (toggle_settings)
			toggle_settings = settings();
		//ImGui::Rect()
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		draw_list->AddCircle(ImVec2(22, 22), 44.0f, ImU32());
		ImGui::Separator();
	}

	{
		static float temp_size = ImGui::GetFontSize() * 2;
		//PushFont(ImGui::GetFont()->ContainerAtlas->Fonts[2]);
		 
		ImGui::Text("%s##Home", ICON_MD_HOME);
		//PopFont();
	}


	ImGui::End();
	
	return toggle_settings;
}

bool BoxerUI_View::settings() {//settings that will replace the sideNav upon toggle
	ImGuiIO& io = ImGui::GetIO();
	bool in_settings = true;
	static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);


	//ImFont* font1 = io.Fonts->AddFontFromFileTTF("font.ttf", size_pixels);
	 /*
	ImGuiIO& io = ImGui::GetIO();*/
	ImFont* font1 = ImGui::GetFont();// = io.Fonts->Fonts[0];

	int size_font = 55;
	//BoxerUI_View::boxerUI_fonts[1]->IsLoaded();
	ImGui::Begin("Settings", 0, flags);

	ImGui::PushFont(font1->ContainerAtlas->Fonts[1]);//BoxerUI_View::boxerUI_font);
	ImGui::Text("Settings");
	ImGui::PopFont();
	//BoxerUI_View::boxerUI_fonts[2].b
	ImGui::Text("%s among %d items", ICON_FA_GOOGLE_WALLET, 2);
	ImGui::Button(ICON_FA_BUFFER " Search");
	//texttheme.title("Settings", &size_font, font);




	ImGui::AlignTextToFramePadding();
	if (ArrowButton("##left", ImGuiDir_Left))
		in_settings = false;
	Spacing();
	Text("Setting"); SameLine();
	HelpMarker("Set values here");
	static bool keyboard = false;

	ImGui::PushFont(font1->ContainerAtlas->Fonts[2]);//BoxerUI_View::boxerUI_font);
	ImGui::Text("Inputs");
	ImGui::PopFont();

	//static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
	if (ImGui::Checkbox("Keyboard", &keyboard))// &flags, ImGuiItemStatusFlags_Focused))
	{
		//keyboard = !keyboard;
		cout << keyboard << endl;


	}
	//keyboard ? input_type = InputType::Keyboard : input_type = InputType::None;
	/*else{cout << "Keyboard Not Selected" << endl;
		}*/

		keyboard ? io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard : ImGuiConfigFlags_NavEnableGamepad;
		
		//keyboard?input_type = InputType::Keyboard:input_type = InputType::None;
		//ImGuiConfigFlags_NavEnableGamepad = !ImGuiConfigFlags_NavEnableGamepad;
		/*else{cout << "Keyboard Not Selected" << endl;
			}*/
	

		// Edit a color (stored as ~4 floats)
		//ImGui::ColorEdit4("Color", my_color);

		// Plot some values
	const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
	ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");

	ImGui::End();
	
	return in_settings;
}


void BoxerUI_View::resetFrame() {
	//Current frame is discarded and renders a new one upon call.
	ImGui::EndFrame();
	ImGui::UpdatePlatformWindows();
	ImGui::Render();
	ImGui::NewFrame();
}
void BoxerUI_View::HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void BoxerUI_View::indexView() {
	sideNav();
	plotStream();
	showdemos();
	appFrameRate();
}

