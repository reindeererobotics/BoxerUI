#pragma once
#include "Boxer.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

enum class InputType  {//same as an enum but with a scope
	None		,
	Keyboard	,
	Gamepad		,
	Joystick	,
	Touch		
};

class Inputs
{
	//ImGuiIO& io = ImGui::GetIO();

private:

	void keyboardInputHandler();
	void gamepadInputHandler();
	void joystickInputHandler();
	void touchInputHandler();
	void noInputHandler();

	void endFrame();
	void beginFrame();
	//static void keyboardInput();
public:
	void inputHandler();

};
 static Inputs input;
static InputType input_type;
//static ImGuiIO& io = ImGui::GetIO();


