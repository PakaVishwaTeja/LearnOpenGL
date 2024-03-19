#version 330 core
in vec3 vertexColor;
in vec2 texCoord;
//uniform vec4 ourColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 FragColor;
void main(){
 //FragColor = vec4(0.4f, 0.0f, 0.0f, 1.0f);
 //FragColor =vec4(vertexColor,1.0);
 FragColor = mix(texture(texture1, texCoord) , texture(texture2 , texCoord), 0.2);
}