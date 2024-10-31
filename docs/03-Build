# Creating a Build Script for Your Project

In this blog, I'll guide you through creating a build script for a simple C++ project using Visual Studio's command line tools. This will allow you to automate the process of compiling and linking your code, ensuring you have a consistent, repeatable build process. We'll use a batch script (`build.bat`) to make things easier. Let's dive in step-by-step.

## Why Use a (.bat) File for Building?

We’re using a `.bat` file instead of CMake or Visual Studio build system for a few reasons:

- **Simplicity and Control**: It lets you directly see and tweak every build command, making it ideal for learning how the process works step-by-step.

- **Less Abstraction**: Unlike CMake, which adds an abstraction layer, a batch script is straightforward for small projects, offering flexibility without unnecessary overhead.

- **Foundation for Future Tools**: It’s a great way to understand the basics before moving to more sophisticated build tools.

In the next section, we’ll learn to use CMake

```bat
:: Path to Visual Studio vcvars64.bat
set VC_VARS_BAT="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"

:: Path to Vendor Libraries
set VENDOR_LIBS=lib

:: GLFW Library to Link
set GLFW_LIBS=%VENDOR_LIBS%\GLFW\glfw3.lib

:: Source Directory
set SRC_DIR=.\src

:: Object Files Directory
set OBJ_DIR=build\obj

:: Executable Output Directory
set EXE_DIR=build

:: Compilation Options
set COMPILER_OPTIONS=/std:c++17 /c /EHsc

:: Additional Libraries to Link
set ADDITIONAL_LIBS=user32.lib gdi32.lib shell32.lib

@echo off
cls

:: Reset environment variables to avoid them growing too long
setlocal

:: Check if Developer Command Prompt for VS 2019 is open
powershell -Command "if (-not(Get-Process | Where-Object { $_.MainWindowTitle -eq 'Developer Command Prompt for VS 2019' })) { exit 0 } else { exit 1 }"

:: If not open, run vcvars64.bat to set up environment
if %errorlevel% equ 0 (
       call %VC_VARS_BAT%
) else (
    echo "Failed to set up Visual Studio environment."
    exit /b 1
)

:: Set up directories
if exist %EXE_DIR% (
    rd /s /q %EXE_DIR%
)

mkdir %EXE_DIR%
mkdir %OBJ_DIR%

:: Compile the source files using configuration
cl.exe %COMPILER_OPTIONS% ^
    /I %VENDOR_LIBS% ^
    /I %VENDOR_LIBS%\GSL\include ^
    /I %SRC_DIR% ^
    %SRC_DIR%\*.cpp ^
    /Fo%OBJ_DIR%\

:: Check for compilation errors
if %errorlevel% neq 0 (
    echo "Compilation failed. Check the error messages above."
    exit /b 1
)

:: Link object files and create the executable
link.exe %OBJ_DIR%\*.obj ^
    %GLFW_LIBS% ^
    %ADDITIONAL_LIBS% ^
    /NODEFAULTLIB:LIBCMT ^
    /OUT:%EXE_DIR%\main.exe

:: Check for linking errors
if %errorlevel% neq 0 (
    echo "Linking failed. Check the error messages above."
    exit /b 1
)

endlocal

echo "Build succeeded. Executable created at: %EXE_DIR%\main.exe"
exit /b 0
```

### Step 2: Modify the Visual Studio Environment Path

The first thing you need to do is modify the path to `vcvars64.bat` so that it matches your machine's installation of Visual Studio. This batch file (`vcvars64.bat`) is essential for setting up the required environment variables for compiling with Visual Studio's tools.

```bat
set VC_VARS_BAT="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
```

Update this path to match the location on your system. If you're using a different version of Visual Studio, make sure to update the version number accordingly.

### Step 3: Understand the Build Script

Let me break down what the script does:

1. **Set Environment Variables**: 

    ```bat
    :: Path to Visual Studio vcvars64.bat
    set VC_VARS_BAT="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"

    :: Path to Vendor Libraries
    set VENDOR_LIBS=lib

    :: GLFW Library to Link
    set GLFW_LIBS=%VENDOR_LIBS%\GLFW\glfw3.lib

    :: Source Directory
    set SRC_DIR=.\src

    :: Object Files Directory
    set OBJ_DIR=build\obj

    :: Executable Output Directory
    set EXE_DIR=build

    :: Compilation Options
    set COMPILER_OPTIONS=/std:c++17 /c /EHsc

    :: Additional Libraries to Link
    set ADDITIONAL_LIBS=user32.lib gdi32.lib shell32.lib
    ```
    
    Paths to essential tools and libraries are set at the beginning, such as `VC_VARS_BAT`, `VENDOR_LIBS`, and `GLFW_LIBS`. These make the script more manageable and easy to modify if paths change.

2. **Check Visual Studio Environment**:

    ```bat
    :: Check if Developer Command Prompt for VS 2019 is open
    powershell -Command "if (-not(Get-Process | Where-Object { $_.MainWindowTitle -eq 'Developer Command Prompt for VS 2019' })) { exit 0 } else { exit 1 }"

    :: If not open, run vcvars64.bat to set up environment
    if %errorlevel% equ 0 (
           call %VC_VARS_BAT%
    ) else (
        echo "Failed to set up Visual Studio environment."
        exit /b 1
    )
    ```
    
    The script uses PowerShell to check if the Developer Command Prompt is open. If it's not, it will call `vcvars64.bat` to set up the necessary environment variables.

3. **Set Up Directories**:

    ```bat
    :: Set up directories
    if exist %EXE_DIR% (
        rd /s /q %EXE_DIR%
    )

    mkdir %EXE_DIR%
    mkdir %OBJ_DIR%
    ```
    
    It creates the necessary directories for object files (`OBJ_DIR`) and the executable (`EXE_DIR`). If these directories already exist, they are deleted to ensure a clean build.

4. **Compile the Code**:

    ```bat
    :: Compile the source files using configuration
    cl.exe %COMPILER_OPTIONS% ^
        /I %VENDOR_LIBS% ^
        /I %VENDOR_LIBS%\GSL\include ^
        /I %SRC_DIR% ^
        %SRC_DIR%\*.cpp ^
        /Fo%OBJ_DIR%\
    ```
    
    The script compiles all `.cpp` files in the source directory (`SRC_DIR`) using `cl.exe` (the Visual Studio compiler) and stores the resulting object files in `OBJ_DIR`.

5. **Link Object Files**:

    ```bat
    :: Link object files and create the executable
    link.exe %OBJ_DIR%\*.obj ^
        %GLFW_LIBS% ^
        %ADDITIONAL_LIBS% ^
        /NODEFAULTLIB:LIBCMT ^
        /OUT:%EXE_DIR%\main.exe
    ```
    
    Once compilation is complete, it uses `link.exe` to link all object files and create the final executable in `EXE_DIR`.

6. **Error Checking**:

    ```bat
    :: Check for compilation errors
    if %errorlevel% neq 0 (
        echo "Compilation failed. Check the error messages above."
        exit /b 1
    )

    :: Check for linking errors
    if %errorlevel% neq 0 (
        echo "Linking failed. Check the error messages above."
        exit /b 1
    )
    ```
    
    After each step, the script checks for errors. If something goes wrong during compilation or linking, an error message will be displayed, and the script will exit.

### Step 4: Run the Build Script

To build your project, open the Developer Command Prompt for Visual Studio and navigate to the folder containing `build.bat`. Then run:

```bat
build.bat
```

If everything is set up correctly, the script will compile and link your project, creating an executable (`main.exe`) in the `build` directory.

### Conclusion

By automating your build process using this `build.bat` script, you can easily compile and link your project with a single command. This can save time and help you maintain consistency across builds.

Feel free to modify this script to suit your project's needs. For instance, you might add more libraries to link, change the compiler options, or even add custom post-build steps.

If you have any questions or run into issues, leave a comment below, and I'll be happy to help! Happy coding!

