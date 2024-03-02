cmake_minimum_required (VERSION 2.8)
#give project name
project (learn_OpenGL)

#version number
set (learn_OpenGL_VERSION_MAJOR 3)
set (learn_OpenGL_VERSION_MINOR 0)

#indicate the entry point for the executable
add_executable ( ${PROJECT_NAME}  main.cpp)

#include the subdirectory containing our libs
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glad)

#adds an include directory to a target
target_include_directories(${PROJECT_NAME}
 PUBLIC PUBLIC ${CMAKE_SOURCE_DIR}/external/glfw/include
 PUBLIC PUBLIC ${CMAKE_SOURCE_DIR}/external/glad/include
 PUBLIC PUBLIC ${CMAKE_SOURCE_DIR}/include
 )

#specifies the library search directories for the linker during target building.
target_link_directories(${PROJECT_NAME}  
PRIVATE PUBLIC ${CMAKE_SOURCE_DIR}/external/glfw/src
PRIVATE PUBLIC ${CMAKE_SOURCE_DIR}/external/glad/src
)

#specifies libraries or targets to be linked during the build process.
target_link_libraries (${PROJECT_NAME}   glfw  glad)