
# Project Structure Setup

## Step  1. Create the Project Directory

1. **Create the Root Folder**:
   - Start by creating the directory called `Vulkan`. This will be the root folder for your this guide.
   - Inside`Vulkan`, create a folder called `00-EmptyWindow`.

## Step  2. Setting Up the (lib) Directory

1. **Create the (lib) Folder**:
   - Inside `00-EmptyWindow`, create a folder called `lib`. This will house external libraries like GLFW and GLM.

2. **Add GLFW Headers and Lib**:
   - Inside `lib`, create another folder named `GLFW`.
   - Copy the contents of the `glfw-3.4.bin.WIN64/include/GLFW` folder from the from the extracted GLFW library into our `00-EmptyWindow/lib/GLFW`.
   - This will provide the necessary GLFW headers for your project.
   - Copy the contents of the `glfw-3.4.bin.WIN64/lib-vc2019` folder from the extracted GLFW library into our `00-EmptyWindow/lib/GLFW`.

3. **Add GLM**:
   - Inside `lib`, create another folder named `glm`.
   - Copy the contents of the `glm-1.0.1-light\glm` folder from the from the extracted glm library into our `00-EmptyWindow/lib/glm`.:
     ```plaintext
     lib
     └───glm
         ├───detail
         ├───ext
         ├───gtc
         ├───gtx
         └───simd
     ```

## Step  3. Setting Up the (src) Directory

1. **Create the `src` Folder**:
   - In your main project directory (`00-EmptyWindow`), create a folder named `src`. This is where all your source code files will reside.

2. **Add `utils`**:
   - Inside `src`, create a folder named `utils`.
   - Copy the downloaded `stb_image.h` to utils.

## Final Structure

```dotnetcli
   - 
├───00-EmptyWindow
│   ├───lib
│   │   ├───GLFW
│   │   │       glfw3.dll
│   │   │       glfw3.h
│   │   │       glfw3.lib
│   │   │       glfw3dll.lib
│   │   │       glfw3native.h
│   │   │       glfw3_mt.lib
│   │   │
│   │   └───glm
│   │       ├───detail
│   │       ├───ext
│   │       ├───gtc
│   │       ├───gtx
│   │       └───simd
│   └───src
│       └───utils
│               stb_image.h
```



---

By setting up `lib` with GLFW and GLM, and adding the `src/utils` folder, your project is organized to support external libraries and modular source code. This structure will help in managing dependencies and code organization effectively.
