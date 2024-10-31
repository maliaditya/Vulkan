
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