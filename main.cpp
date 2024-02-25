#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include<fstream>
using namespace std;

GLFWwindow* window;
GLuint VBO;
GLuint VAO;
GLuint EBO;
GLuint gGraphicsPipeline;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void initialize();
void vertexSpecification();
void createGraphicsPipeline();
    string loadShaderAsString( const string &filename);
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


    // if resized, reset glviewport to the new dimns
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

}

void vertexSpecification(){
    GLfloat vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1 , &VBO);
    glGenBuffers(1 , &EBO);

    glBindVertexArray(VAO);

    // bind and give VBO data
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);

    //bind and give ebo data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0,3,GL_FLOAT , GL_FALSE , 3 * sizeof(GLfloat) , (void*)0);
    glEnableVertexAttribArray(0);

    //unbind
    glBindBuffer(GL_ARRAY_BUFFER , 0);
    glBindVertexArray(0); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0);//unbind after unbinding VAO
}
void createGraphicsPipeline(){
    //load shaders
    string vsSrc  = loadShaderAsString("/Users/vishwa/dev/Learn_OpenGL/shaders/vert.glsl");
    string fsSrc  = loadShaderAsString("/Users/vishwa/dev/Learn_OpenGL/shaders/frag.glsl");

    gGraphicsPipeline = createShaderProgram(vsSrc , fsSrc);
}
GLuint createShaderProgram(string vs , string fs){
    GLuint programObject  = glCreateProgram();

    //compiling shader source
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER,vs);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER,fs);

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
  glBindVertexArray(VAO);
//   glDrawArrays(GL_TRIANGLES , 0 , 3);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void cleanup(){
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(gGraphicsPipeline);
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