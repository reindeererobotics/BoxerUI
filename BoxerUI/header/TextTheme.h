#pragma once
#include "Boxer.h"

//extern ImGuiIO& io;
//ImGuiIO& io = ImGui::GetIO();


enum class TextStyle {
	Title = 55,
	Subtitle,
	Body,
	Caption,
	Custom
};

class TextTheme
{


	//ImFont* font2 = io.Fonts->AddFontFromFileTTF("anotherfont.otf", size_pixels);
public:

	void title(const char* text, int* size, ImFont* font);

	void titleStyle(ImFont* title_style, float font_size, const ImFontConfig* font_cfg , const ImWchar* glyph_ranges);

	void customStyle(ImFontConfig config, int font_size);

};
static TextTheme texttheme;




