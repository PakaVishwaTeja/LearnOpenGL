#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include<fstream>
#include<shader.h>
using namespace std;

GLFWwindow* window;
GLuint VBO;
GLuint VAO;
GLuint EBO;
shader* shaderProgram;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void initialize();
void vertexSpecification();
void mainloop();
    void predraw();
    void draw();
void cleanup();

int main(){
    cout<<"hello humans!"<<endl;
    initialize();
    vertexSpecification();
    shaderProgram = new shader(
        "/Users/vishwa/dev/Learn_OpenGL/shaders/vert.glsl",
        "/Users/vishwa/dev/Learn_OpenGL/shaders/frag.glsl"
        );
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
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
}; 
    unsigned int indices[] = {
        0, 1, 2   // first triangle
        //1, 2, 3    // second triangle
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

    //vertex position attribute
    glVertexAttribPointer(0,3,GL_FLOAT , GL_FALSE , 6 * sizeof(GLfloat) , (void*)0);
    glEnableVertexAttribArray(0);
    //vertex color attribute
    glVertexAttribPointer(1,3,GL_FLOAT , GL_FALSE , 6 * sizeof(GLfloat) , (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    //unbind
    glBindBuffer(GL_ARRAY_BUFFER , 0);
    glBindVertexArray(0); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0);//unbind after unbinding VAO
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

    float timeValue = glfwGetTime();
    // float gValue = (sin(timeValue) / 2.0f) + 0.5f;
    // float rValue = (sin(timeValue + 3) / 2.0f) + 0.5f;
    // float bValue = (sin(timeValue + 5) / 2.0f) + 0.5f;

        //  glClearColor function is a _state-setting_ function
        //glClearColor(rValue, gValue,bValue, 1.0f);
        glClearColor(0.2, 0.3,0.2, 1.0f);
        //glClear is a _state-using_ function. 
        //It uses the current state to retrieve the clearing color from.
        glClear(GL_COLOR_BUFFER_BIT);
}
void draw(){

  shaderProgram->use();

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  shaderProgram->setFloat4( "ourColor" ,  0.2,0.2,0.2,1.0);

  glBindVertexArray(VAO);
  //glDrawArrays(GL_TRIANGLES , 0 , 3);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}
void cleanup(){
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
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