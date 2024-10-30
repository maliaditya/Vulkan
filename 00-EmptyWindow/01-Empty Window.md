
# Creating an Empty Window with GLFW

In this blog post, we'll walk through the steps to create an empty window using GLFW, a popular library for managing contexts and windows. This foundational step is often the starting point for any graphics application. We'll look at a C++ implementation that opens a window, displays it, and cleans up resources properly using RAII principles (Resource Acquisition Is Initialization).

## Step 1: Setting Up Your Project

To follow along, make sure you have installed the required dependencies:

- **GLFW**: This library is used to create windows and handle inputs.

Make sure to link the appropriate libraries and set up your environment, for example in Visual Studio or VS Code, to use these dependencies.

## Step 2: Write the Main Application Code

We begin by writing a simple main application that creates a window:

### Main Application Code (main.cpp)

```cpp
// main.cpp
#include "window.h"

int main()
{
    // Create a window with the specified width, height, and title
    Window appWindow(800, 600, "Vulkan: Empty Window");

    // Run the application (main loop)
    appWindow.run();

    // Resources will be automatically cleaned up by RAII (no manual cleanup needed)
    return 0;
}
```

In the `main.cpp` file, we use the `Window` class to create an instance of our window, passing in the desired width, height, and title. The `run()` function starts the main loop of the window application, keeping it open until the user closes it.

## Step 3: Defining the Window Class

Now, let’s define our `Window` class that abstracts the window creation details:

### Window Class Definition (Window.h)

```cpp
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
    // GLFW window object
    GLFWwindow* window;
};
```

In `Window.h`, we define our `Window` class with a constructor, a destructor, and a `run` function. The class also contains a pointer to a `GLFWwindow` that manages the window.

## Step 4: Implementing the Window Class

The implementation of the `Window` class handles window creation, initialization, and clean-up:

### Window Class Implementation (Window.cpp)

```cpp
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

    // Create a windowed mode window
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        std::cerr << "Error: Failed to create GLFW window." << std::endl;  // Error message with std::cerr
        glfwTerminate();  // Clean up GLFW if window creation fails
        std::exit(EXIT_FAILURE);
    }
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

// Main loop function that keeps the window running until closed by the user
void Window::run()
{
    // Check if the window should close
    while (!glfwWindowShouldClose(window))
    {
        // Poll for and process events
        glfwPollEvents();

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }
}
```

## Detailed Explanation

### Constructor (Window::Window)

```cpp
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

    // Create a windowed mode window
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        std::cerr << "Error: Failed to create GLFW window." << std::endl;  // Error message with std::cerr
        glfwTerminate();  // Clean up GLFW if window creation fails
        std::exit(EXIT_FAILURE);
    }
}
```

- The constructor is responsible for acquiring all the necessary resources to create the window.
- We first call `glfwInit()` to initialize GLFW. If it fails, we output an error message using `std::cerr` and terminate the program using `std::exit(EXIT_FAILURE)`. This ensures that if GLFW is not set up correctly, we handle the failure gracefully.
- Next, `glfwCreateWindow()` is called to create the window. We pass the width, height, and title as parameters. If window creation fails, we print an error, terminate GLFW, and exit the program.
- This resource acquisition during the constructor ensures that everything is set up properly before the program proceeds, a concept known as **RAII (Resource Acquisition Is Initialization)**.

### Destructor (Window::~Window)

```cpp
// Destructor: Release resources (RAII - releasing resources)
Window::~Window()
{
    if (window)
    {
        glfwDestroyWindow(window);  // Destroy window (RAII)
    }
    glfwTerminate();  // Terminate GLFW (RAII)
}
```

- The destructor is used to release the resources when the `Window` object goes out of scope or is deleted.
- We use `glfwDestroyWindow()` to destroy the created window, and `glfwTerminate()` to clean up GLFW-related resources.
- This ensures that all resources are properly released, avoiding memory/resource leaks.

### RAII Pattern

- The **RAII** principle is used here to manage the lifecycle of the window resource. The constructor acquires the resources, and the destructor releases them automatically.
- This pattern helps in managing resources more effectively and ensures that cleanup is always performed, even in case of exceptions or early returns.

### run() Method

```cpp
// Main loop function that keeps the window running until closed by the user
void Window::run()
{
    // Check if the window should close
    while (!glfwWindowShouldClose(window))
    {
        // Poll for and process events
        glfwPollEvents();

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }
}
```

- The `run()` function contains the main loop of the application.
- `glfwWindowShouldClose(window)` checks whether the user has requested to close the window.
- `glfwPollEvents()` processes incoming events, such as user inputs.
- `glfwSwapBuffers(window)` swaps the front and back buffers to display the updated frame.
- This loop keeps the window open and responsive until the user decides to close it.

## Conclusion

Congratulations! You've successfully implemented a basic application that opens an empty window using GLFW in C++. Understanding window creation is the first building block towards building more advanced applications. In future tutorials, we will dive into adding rendering capabilities, handling user inputs, and building interactive 3D applications.

### Next Steps

You can enhance this program by adding input handling (keyboard and mouse), rendering a simple shape, or even using an image as an icon for the window (as hinted by the `stb_image` import in the code). Make sure to check out the GLFW documentation for more details on how to do that.
