#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

GLFWwindow* window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void initialize();
void mainloop();
    void predraw();
    void draw();
void cleanup();

int main(){
    cout<<"hello humans!"<<endl;

    initialize();
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

    // with this OpenGL knows how we want to display the data and coordinates with respect to the window
    //i.e. maps -1 to 1 to 0 to 800
    glViewport(0, 0, 800, 600);
    // if resized, reset glviewport to the new dimns
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

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