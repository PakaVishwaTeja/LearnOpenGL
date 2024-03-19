#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
class shader{
    public:
        GLuint id;
        shader(string vs , string fs){

            string vsSrc  = loadShaderAsString(vs);
            string fsSrc  = loadShaderAsString(fs);

            id = glCreateProgram();

            //compiling shader source
            GLuint vertexShader = compileShader(GL_VERTEX_SHADER,vsSrc);
            GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER,fsSrc);

            //linking shaders to program object i.e graphics pipeline
            glAttachShader(id , vertexShader);
            glAttachShader(id , fragmentShader);
            glLinkProgram(id);
            glValidateProgram(id);

               // Check for shader program linking errors
            GLint success;

            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetProgramInfoLog(id, 512, NULL, infoLog);
                std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
                exit(1);
            }
        };
        ~shader(){
            glDeleteProgram(this->id);
        }

        void use() { 
            glUseProgram(id); 
        }
        
        void setFloat4(const std::string &name, float v1 , float v2 ,float v3 ,float v4){
            int location = glGetUniformLocation(id , name.c_str());
            glUniform4f(location, v1,v2,v3,v4);
        }
        void setMat4(const std::string &name, glm::mat4 model){
            int location = glGetUniformLocation(id , name.c_str());
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));
        }
        
    private:
        GLuint compileShader(GLuint type ,string src){
            GLuint shaderObject;
            shaderObject = glCreateShader(type);

            const char* source = src.c_str();
            GLint codelength[1];
            codelength[0] = strlen(source);

            glShaderSource(shaderObject , 1 , &source ,codelength );
            glCompileShader(shaderObject);

            // Check for  shader compilation errors
            GLint success;
            glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
                std::cerr << ((type == 35633)?"GL_VERTEX_SHADER":"GL_FRAGMENT_SHADER") << "compilation failed:\n" << infoLog << std::endl;
                return -1;
            }

            return shaderObject;
        }
        string loadShaderAsString( const string &filename){
            string result = "";
            string line = "";
            ifstream myFile;
            myFile.open(filename);
            if(myFile.is_open()){
                while(getline(myFile , line)){
                    result += line + '\n';
                }
                myFile.close();
            }else{
                std::cerr << "Error opening file: " << strerror(errno) << std::endl;
                cout<<filename<<" not opened!"<<endl;
            }
            return result;
        }
};

#endif