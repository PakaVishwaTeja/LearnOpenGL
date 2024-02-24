# 1. Setting things up!
### Steps Overview


1.1 **Setting up the Basics**
- [referance commit](https://github.com/PakaVishwaTeja/LearnOpenGL/commit/7716ab9463355a68dddc1e10ab9db890d5402815)
```
    
    - Initialize a Git repository for version control.
    - Configure basic CMake and build scripts.
    
```
1.2 **Bringing in the Crew: GLFW and Glad**
- [setting up GLFW commit](https://github.com/PakaVishwaTeja/LearnOpenGL/commit/2a907a9549feace1287f3276c3363b59ad863f25)
- [setting up glad commit](https://github.com/PakaVishwaTeja/LearnOpenGL/commit/2cebcf8914fbb1ccd03c63ec7e52039b09408cde)
```
	
	- Incorporate GLFW for window management.
    - Add Glad to access OpenGL functions from hardware.
    
```

>[!NOTE]
>OpenGL development requires 
>- GLFW for window management 
>- Glad for accessing hardware-specific OpenGL functions.

## 1.1 **Setting up the Basics**
### 1.1.1 Git
- Initialize a Git repository. 
- Add `main.cpp` file .
### 1.1.2 CMake
-  In the root of the project directory, add a `CMakeLists.txt`:
```
cmake_minimum_required (VERSION 2.8)
#give project name
project (learn_OpenGL)

#version number
set (learn_OpenGL_VERSION_MAJOR 3)
set (learn_OpenGL_VERSION_MINOR 0)

#indicate the entry point for the executable
add_executable ( ${PROJECT_NAME}  main.cpp)

```
### 1.1.3 Configure, Build, and Run Scripts

To streamline the process, we're adding these scripts to `/scripts` and creating `out/build` directories.

```
//configure.sh
cmake  -S ../ -B ../out/build

//build.sh
cd ../out/build
make

//run.sh
cd ../out/build
./learn_OpenGL
```

>[!TIP] 
>Excellent! Now, if we execute:
>
>```
>bash scripts/configure.sh 
>bash scripts/build.sh 
>bash scripts/run.sh 
>```
>We'll see our "Hello Humans!" in action!



## 1.2 **Bringing in the Crew: GLFW and Glad**
### 1.2.1  Integrating GLFW

#### 1.2.1.1 Adding GLFW as a Submodule

Add GLFW repository as a submodule within our project at `external/glfw` directory:

```
git submodule add https://github.com/glfw/glfw.git external/glfw
```

#### 1.2.1.2 CMake Changes

Update the project's CMake configuration in the root directory:

```cmake
# ./CMakeLists.txt
...

#include the subdirectory containing our libs
add_subdirectory(${PROJECT_NAME}/external/glfw)

# Include GLFW headers
target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include)

# Link GLFW library
target_link_directories(${PROJECT_NAME} PUBLIC external/glfw/src)
target_link_libraries(learnOpenGL glfw)

```

This ensures that the linker searches for GLFW libraries in the specified directory when building the target.


>[!TIP]
>Verify the integration by adding 
>
>```
>#include <GLFW/glfw3.h>
>```
>
> into `main.cpp` and building the project.


### 1.2.2  Integrating GLAD

- Go to [GLAD website](https://glad.dav1d.de/)
- Configure:
    - Language: C/C++
    - API: OpenGL
    - OpenGL version: 3.3
    - Profile: Core
    - Check "Generate a loader"
- Generate the files download glad.zip
- Add the generated folder to `external/`
- Create a CMake file for GLAD in `external/glad/`
```
#external/glad/CmakeLists.txt

#generates glad lib 
add_library (glad
include/glad/glad.h
src/glad.c)

#include dirs for glad
target_include_directories(glad
PUBLIC include)
```

Now, in the project's root CMake:
- Add GLAD similar to the changes for GLFW. ([[#^4090cf|Cmake changes for GLFW1.2.1.2 ]])


>[!TIP]
>Verify the integration by adding
>```
>#include <glad/glad.h>
>```
>into `main.cpp` and building the project we can verify!


# end

>[!TIP]
>now we are all set to create a window!
>