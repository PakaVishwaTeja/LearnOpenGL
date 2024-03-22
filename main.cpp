#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include<fstream>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<shader.h>
#include<camera.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#define STB_IMAGE_IMPLEMENTATION

using namespace std;
bool firstMouse = true;
int HEIGHT = 800, WIDTH = 800;
float lastX = HEIGHT/2, lastY = WIDTH/2;


camera* cam;

GLFWwindow* window;
GLuint VBO;
GLuint VAO;
GLuint EBO;
shader* shaderProgram;
GLuint texture1;
GLuint texture2;



float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void processInput(GLFWwindow *window);

void initialize();
void vertexSpecification();
void setTextures();
void mainloop();
    void predraw();
    void draw();
void cleanup();

int main(){
    cout<<"hello humans!"<<endl;

    initialize();
    vertexSpecification();
    setTextures();

    cam = new camera();
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
    window = glfwCreateWindow(800, 800, "LearnOpenGL vishwa", NULL, NULL);
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, mouse_callback);  
    glfwSetScrollCallback(window, scroll_callback); 


}

void vertexSpecification(){
// GLfloat vertices[] = {
//     // positions          // colors           // texture coords
//      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//     -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
// };
GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
    unsigned int indices[] = {
        0, 1, 3 ,  // first triangle
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

    //vertex position attribute
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 5*sizeof(GLfloat) , (void*)0);
    glEnableVertexAttribArray(0);
    // //vertex position attribute
    // glVertexAttribPointer(0,3,GL_FLOAT , GL_FALSE , 8 * sizeof(GLfloat) , (void*)0);
    // glEnableVertexAttribArray(0);
    // //vertex color attribute
    // glVertexAttribPointer(1,3,GL_FLOAT , GL_FALSE , 8 * sizeof(GLfloat) , (void*)(3*sizeof(GLfloat)));
    // glEnableVertexAttribArray(1);
    //vertex tex coords
    glVertexAttribPointer(2,2,GL_FLOAT , GL_FALSE , 5 * sizeof(GLfloat) , (void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);


    //unbind
    glBindBuffer(GL_ARRAY_BUFFER , 0);
    glBindVertexArray(0); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0);//unbind after unbinding VAO
}
void setTextures(){
    glGenTextures(1 , &texture1);
    glBindTexture(GL_TEXTURE_2D , texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("/Users/vishwa/dev/Learn_OpenGL/res/texture.jpeg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1 , &texture2);
    glBindTexture(GL_TEXTURE_2D , texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);  

    data = stbi_load("/Users/vishwa/dev/Learn_OpenGL/res/image.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
void mainloop(){
    shaderProgram->use();

    glEnable(GL_DEPTH_TEST);

    //static uniforms
    glUniform1i(glGetUniformLocation(shaderProgram->id, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram->id, "texture2"), 1);

    /* Loop until the user closes the window */
    while(!glfwWindowShouldClose(window))
    {  
        processInput(window);
        predraw();
        draw();
       
        glfwSwapBuffers(window);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 
    }
}
void predraw(){

    float timeValue = glfwGetTime();
    // float gValue = (sin(timeValue) / 2.0f) + 0.5f;
    // float rValue = (sin(timeValue + 3) / 2.0f) + 0.5f;
    // float bValue = (sin(timeValue + 5) / 2.0f) + 0.5f;


    glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));  
    GLuint transformLoc = glGetUniformLocation(shaderProgram->id , "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
    model = glm::rotate(model, (float)glfwGetTime() *3* glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));  

    // glm::mat4 view = glm::mat4(1.0f);
    // // note that we're translating the scene in the reverse direction of where we want to move
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // glm::mat4 view;
    // view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
  	// 	   glm::vec3(0.0f, 0.0f, 2.0f), 
  	// 	   glm::vec3(0.0f, 1.0f, 0.0f));

    const float radius = 5.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    glm::mat4 view;
    view = cam->getLookAt();
    //std::cout<<glm::to_string(view)<<endl;
    // //  glm::lookAt(cam->cameraPos , cam->cameraPos + cam->cameraFront , cam->cameraUp );

    glm::mat4 projection;
    // projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    projection = glm::perspective(glm::radians(cam->fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    //projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

    shaderProgram->setMat4("model", model);
    shaderProgram->setMat4("view", view);
    shaderProgram->setMat4("proj", projection);
    
        //  glClearColor function is a _state-setting_ function
        //glClearColor(rValue, gValue,bValue, 1.0f);
        glClearColor(0.2, 0.3,0.2, 1.0f);
        //glClear is a _state-using_ function. 
        //It uses the current state to retrieve the clearing color from.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void draw(){
  
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  shaderProgram->setFloat4( "ourColor" ,  0.2,0.2,0.2,1.0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
   
  glBindVertexArray(VAO);
    for(unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i; 
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shaderProgram->setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
  //glDrawArrays(GL_TRIANGLES , 0 , 36);
  //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
    
    WIDTH = width;
    HEIGHT = height;
} 
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    } 
    
    cam->processMouse(xpos - lastX , lastY - ypos);

    lastX = xpos;
    lastY = ypos;

}


void processInput(GLFWwindow *window){
    // handles input
    //checks if any events are triggered & updates the window state
    glfwPollEvents();    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam->processKeyboard(FORWARD,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam->processKeyboard(BACKWARD,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam->processKeyboard(LEFT,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam->processKeyboard(RIGHT,deltaTime);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    cam->porcessScroll(yoffset);
}