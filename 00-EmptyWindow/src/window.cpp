// Window.cpp
#include "window.h"
#include <iostream>  // For std::cout and std::cerr
#include <cstdlib>   // For std::exit
#define STB_IMAGE_IMPLEMENTATION
#include "utils/stb_image.h"  // For loading the window icon

// Constructor: Create window and initialize variables (RAII - acquiring resources)
Window::Window(int width, int height, const char* title)
    : window(nullptr)  // Initialize members
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Error: Failed to initialize GLFW." << std::endl;  // Error message with std::cerr
        std::exit(EXIT_FAILURE);  // Exit if GLFW can't be initialized
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        std::cerr << "Error: Failed to create GLFW window." << std::endl;  // Error message with std::cerr
        glfwTerminate();  // Clean up GLFW if window creation fails
        std::exit(EXIT_FAILURE);
    }

    // Set callbacks for input events
    glfwSetKeyCallback(window, keyboard);
    glfwSetMouseButtonCallback(window, mouse);

    // Set the window icon
    setWindowIcon();
}

// Destructor: Release resources (RAII - releasing resources)
Window::~Window()
{
    if (window)
    {
        glfwDestroyWindow(window);  // Destroy window (RAII)
    }
    glfwTerminate();  // Terminate GLFW (RAII)
}

// Function to set the window icon
void Window::setWindowIcon()
{
    int width, height, channels;
    unsigned char* image = stbi_load("aditya.png", &width, &height, &channels, 4);  // Load a 32-bit PNG image

    if (image)
    {
        GLFWimage icon;
        icon.width = width;
        icon.height = height;
        icon.pixels = image;

        glfwSetWindowIcon(window, 1, &icon);  // Set the icon for the window
        stbi_image_free(image);  // Free the loaded image data
    }
    else
    {
        std::cerr << "Error: Failed to load icon image 'aditya.png'." << std::endl;  // Error message with std::cerr
    }
}

// Main loop function
void Window::run()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

// Keyboard input handler (static function)
void Window::keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);  // Close window on ESC key press
            break;
        default:
            break;
        }
    }
}

// Mouse button input handler (static function)
void Window::mouse(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);  // Close window on left mouse button click
    }
}
