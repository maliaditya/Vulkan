// main.cpp
#include "window.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

int main()
{
    // Create a window with the specified width, height, and title
    Window appWindow(800, 600, "Aditya Shivaji Mali - Window with Icon");

    // Run the application (main loop)
    appWindow.run();

    // Resources will be automatically cleaned up by RAII (no manual cleanup needed)
    return 0;
}
