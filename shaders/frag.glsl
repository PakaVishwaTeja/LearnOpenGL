#version 330 core
in vec3 vertexColor;
//uniform vec4 ourColor;

out vec4 FragColor;
void main(){
 //FragColor = vec4(0.4f, 0.0f, 0.0f, 1.0f);
 FragColor =vec4(vertexColor,1.0);
}