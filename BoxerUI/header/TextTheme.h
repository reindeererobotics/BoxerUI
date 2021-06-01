#pragma once

//extern ImGuiIO& io;
//ImGuiIO& io = ImGui::GetIO();


enum TextTheme {
	Title=20,
	Subtitle,
	Body,
	Caption,
	Custom=12
};

void titleStyle(ImFont* title_style, float font_size=Title, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL) {
	const char* font_type = "resource\\fonts\\PantonDemo-Black.otf"; 
	//title_style = io.Fonts->AddFontFromFileTTF(font_type, font_size);
}

void customStyle(ImFontConfig config, float font_size=Custom) {//TODO: Complete building a default fontstyle model

	config.OversampleH = 2;
	config.OversampleV = 1;
	config.GlyphExtraSpacing.x = 1.0f;
	//ImFont* font = io.Fonts->AddFontFromFileTTF("font.ttf", font_size, &config);
}