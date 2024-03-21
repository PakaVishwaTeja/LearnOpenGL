#generates glad lib 
add_library (glad
include/glad/glad.h
src/glad.c)

#include dirs for glad
target_include_directories(glad
PUBLIC include)