#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

using namespace std;

#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 300

int main(void)
{
    GLFWwindow* window;

    //library
    if (!glfwInit())
    {
        return -1;
    }
    
    // Create a windowed mode window and its OpenGL context
    
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Controller Input", NULL, NULL);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    
    // Loop until  closes the window
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
     
        int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
        std::cout << "Controller status :"<<present << std::endl;

        if (1 == present)
        {
            int axesCount;
            const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
            
            cout << endl;
            cout << endl;
            cout << endl;
            cout <<endl;
            cout <<endl;
            cout <<endl;
            cout <<endl;
            cout <<endl;
            
            
            cout << "Left Stick X Axis: " << axes[0] << endl; // range -1-1
            cout << "Left Stick Y Axis: " << -axes[1] << endl; // range -1-1
            cout << "Right Stick X Axis: " << axes[2] << endl; // range -1-1
            cout << "Right Stick Y Axis: " << -axes[3] << endl; // range -1-1
            cout << "Left Trigger: " << axes[4]+1 << endl; //range 0-2
            cout << "Right Trigger: " << axes[5]+1 << endl; //range 0-2
            

            int buttonCount;
            const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
            
            if (GLFW_PRESS == buttons[0])
            {
                cout << "A Pressed" << endl;
            }
            else if (GLFW_RELEASE == buttons[0])
            {
                cout << "A Released" << endl;
            }
            
            if (GLFW_PRESS == buttons[1])
            {
                cout << "B Pressed" << endl;
            }
            else if (GLFW_RELEASE == buttons[1])
            {
                cout << "B Released" << endl;
            }
           
            if (GLFW_PRESS == buttons[2])
            {
                cout << "X Pressed" << endl;
            }
            else if (GLFW_RELEASE == buttons[2])
            {
                cout << "X Released" << endl;
            }

            if (GLFW_PRESS == buttons[3])
            {
                cout << "Y Pressed" << endl;
            }
            else if (GLFW_RELEASE == buttons[3])
            {
                cout << "Y Released" << endl;
            }

            if (GLFW_PRESS == buttons[4])
            {
                cout << "LB Pressed" << endl;
            }
            else if (GLFW_RELEASE == buttons[4])
            {
                cout << "LB Released" << endl;
            }

            if (GLFW_PRESS == buttons[5])
            {
                cout << "RB Pressed" << endl;
            }
            else if (GLFW_RELEASE == buttons[5])
            {
                cout << "RB Released" << endl;
            }

            if (GLFW_PRESS == buttons[6])
            {
                cout << "B7 Pressed" << endl;
            }
            else if (GLFW_RELEASE == buttons[6])
            {
                cout << "B7 Released" << endl;
            }

            if (GLFW_PRESS == buttons[7])
            {
                cout << "B8 Pressed" << endl;
            }
            else if (GLFW_RELEASE == buttons[7])
            {
                cout << "B8 Released" << endl;
            }

            if (GLFW_PRESS == buttons[8])
            {
                cout << "Left Axis Pressed" << endl;
            }
            else if (GLFW_RELEASE == buttons[8])
            {
                cout << "Left Axis Released" << endl;
            }

            if (GLFW_PRESS == buttons[9])
            {
                cout << "Right Axis Pressed" << endl;
            }
            else if (GLFW_RELEASE == buttons[9])
            {
                cout << "Right Axis Released" << endl;
            }

            if (GLFW_PRESS == buttons[10])
            {
                cout << "Up Pressed" << endl;
            }
            else if (GLFW_RELEASE == buttons[10])
            {
                cout << "Up Released" << endl;
            }       

            if (GLFW_PRESS == buttons[11])
            {
                cout << "Right Pressed" << endl;
            }
            else if (GLFW_RELEASE == buttons[11])
            {
                cout << "Right Released" << endl;
            }

            if (GLFW_PRESS == buttons[12])
            {
                cout << "Down Pressed" << endl;
            }
            else if (GLFW_RELEASE == buttons[12])
            {
                cout << "Down Released" << endl;
            }

            if (GLFW_PRESS == buttons[13])
            {
                cout << "Left Pressed" << endl;
            }
            else if (GLFW_RELEASE == buttons[13])
            {
                cout << "Left Released" << endl;
            }
           

            const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
            cout << name << endl;
        }



        
        // Swap front and back buffers
        glfwSwapBuffers(window);
        
        // Poll for and process events
        glfwPollEvents();
    
    }
    
    glfwTerminate();

    return 0;
}