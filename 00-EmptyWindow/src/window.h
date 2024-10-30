// Window.h
#pragma once

#include <GLFW/glfw3.h>

class Window
{
public:
    // Constructor acquires resources (creates window and initializes GLFW)
    Window(int width, int height, const char* title);

    // Destructor releases resources (destroys window and terminates GLFW)
    ~Window();

    // Main loop function
    void run();

private:
    // Event handling
    static void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse(GLFWwindow* window, int button, int action, int mods);

    // Function to set the window icon
    void setWindowIcon();

    // GLFW window object
    GLFWwindow* window;
};
