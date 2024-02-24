# 1. Setting things up!
### Steps Overview

1.1 **Setting up the Basics**
    
    - Initialize a Git repository for version control.
    - Configure basic CMake and build scripts.
    
1.2 **Bringing in the Crew: GLFW and Glad**
    
    - Incorporate GLFW for window management.
    - Add Glad to access OpenGL functions from hardware.


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

project (learnOpenGL)

#version number
set (hello_VERSION_MAJOR 3)
set (hello_VERSION_MINOR 0)

#indicate the entry point for the executable
add_executable ( ${PROJECT_NAME} main.cpp)

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

>[!success] Excellent! Now, if we execute:
>_
>
>```
>bash scripts/configure.sh 
>bash scripts/build.sh 
>bash scripts/run.sh 
>```
>We'll see our "Hello Humans!" in action!




