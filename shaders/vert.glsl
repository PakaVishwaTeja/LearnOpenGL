#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;
void main(){
  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
  vertexColor = vec4(0.8,0.4,0.5,1.0);
}