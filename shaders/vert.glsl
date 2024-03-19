#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
out vec3 vertexColor;
out vec2 texCoord;
void main(){
  gl_Position = proj*view*model*transform * vec4(aPos, 1.0f);
  vertexColor = aColor;
  texCoord = aTexCoord;
}