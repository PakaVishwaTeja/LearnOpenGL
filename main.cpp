#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include<fstream>
using namespace std;

GLFWwindow* window;
GLuint VBO;
GLuint VAO;
GLuint gGraphicsPipeline;
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void initialize();
void vertexSpecification();
void createGraphicsPipeline();
    string loadShaderAsString( string filename);
        GLuint createShaderProgram(string vs , string fs);
            GLuint compileShader(GLuint type ,string src);
void mainloop();
    void predraw();
    void draw();
void cleanup();

int main(){
    cout<<"hello humans!"<<endl;

    initialize();
    vertexSpecification();
    createGraphicsPipeline();
    mainloop();
    cleanup();
 // Define the vertices of the triangle
 


    return 0;
}
void initialize(){
    /* Initialize the library */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "LearnOpenGL vishwa", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //load glad to get opengl functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }   

    // with this OpenGL knows how we want to display the data and coordinates with respect to the window
    //i.e. maps -1 to 1 to 0 to 800
    glViewport(0, 0, 800, 600);
    // if resized, reset glviewport to the new dimns
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

}

void vertexSpecification(){
    GLfloat vertices[] = {
        -0.5f , -0.5f , 0.0f,
        0.5f , -0.5f , 0.0f,
        0.0f , 0.5f , 0.0f
    };
    
    glGenBuffers(1 , &VBO);


    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT , GL_FALSE , 3 * sizeof(GLfloat) , (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER , 0);
}
void createGraphicsPipeline(){
    //load shaders
    string vsSrc  = loadShaderAsString("../../shaders/vert.glsl");
    string fsSrc  = loadShaderAsString("../../shaders/frag.glsl");

    gGraphicsPipeline = createShaderProgram(vsSrc , fsSrc);
}
GLuint createShaderProgram(string vs , string fs){
    GLuint programObject  = glCreateProgram();

    //compiling shader source
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER,vs);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER,vs);

    //linking shaders to program object i.e graphics pipeline
    glAttachShader(programObject , vertexShader);
    glAttachShader(programObject , fragmentShader);
    glLinkProgram(programObject);
    glValidateProgram(programObject);
        // Check for shader program linking errors
            GLint success;

    glGetProgramiv(programObject, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(programObject, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
        return -1;
    }

    return programObject;
}
GLuint compileShader(GLuint type ,string src){
    GLuint shaderObject;
    shaderObject = glCreateShader(type);

    const char* source = src.c_str();
    GLint codelength[1];
    codelength[0] = strlen(source);

    glShaderSource(shaderObject , 1 , &source ,codelength );
    glCompileShader(shaderObject);

    // Check for vertex shader compilation errors
    GLint success;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
        return -1;
    }

    return shaderObject;
}
string loadShaderAsString( string filename){
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
        cout<<filename<<" not opened!"<<endl;
    }
    return result;
}

void mainloop(){
    /* Loop until the user closes the window */
    while(!glfwWindowShouldClose(window))
    {  
        processInput(window);
        predraw();
        draw();
       
       
        glfwSwapBuffers(window);
    }
}
void predraw(){
        //  glClearColor function is a _state-setting_ function
        glClearColor(0.0f, 0.5f, 0.3f, 1.0f);
        
        //glClear is a _state-using_ function. 
        //It uses the current state to retrieve the clearing color from.
        glClear(GL_COLOR_BUFFER_BIT);
}
void draw(){
  glUseProgram(gGraphicsPipeline);
  glBindBuffer(GL_ARRAY_BUFFER , VBO);
  glDrawArrays(GL_TRIANGLES , 0 , 3);
}
void cleanup(){
    //clean glfw
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
} 

void processInput(GLFWwindow *window){
    // handles input
    //checks if any events are triggered & updates the window state
    glfwPollEvents();    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}