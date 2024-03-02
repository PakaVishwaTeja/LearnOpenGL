#version 330 core
in vec4 vertexColor;
out vec4 FragColor;
void main(){
 //FragColor = vec4(0.4f, 0.0f, 0.0f, 1.0f);
 FragColor =vertexColor;
}