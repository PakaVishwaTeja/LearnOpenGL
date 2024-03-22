#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float CAMERA_SPEED       =  2.5f;
const float MOUSE_SENSITIVITY =  0.1f;
const float FOV        =  45.0f;


enum camera_movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class camera{
    public:
    float yaw ;
    float pitch ;
    
    float fov ;

    const float cameraSpeed; 
    const float mouseSensitivity; 


    glm::vec3 pos   ;
    glm::vec3 front ;
    glm::vec3 up    ;
    glm::vec3 right ;

    camera( glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3 u = glm::vec3(0.0f, 1.0f, 0.0f),
            float y = YAW,
            float p = PITCH) 
            : 
            front(glm::vec3(0.0f, 0.0f, -1.0f)),
            cameraSpeed(CAMERA_SPEED),
            mouseSensitivity(MOUSE_SENSITIVITY),
            fov(FOV){
                pos = position;
                up  = u;
                yaw = y;
                pitch = p; 
                // right = glm::normalize(glm::cross(front,up));
                updateCameraVectors();
            }
        


    glm::mat4 getLookAt(){
        return glm::lookAt(pos , pos + front , up);
    }

    void processKeyboard(camera_movement direction , float deltaTime){
        float displacement = cameraSpeed * deltaTime;
        if (direction == FORWARD)
            pos += front * displacement;
        if (direction == BACKWARD)
            pos -= front * displacement;
        if (direction == LEFT)
            pos -= right * displacement;
        if (direction == RIGHT)
            pos += right * displacement;
    }

    void processMouse(double xoffset, double yoffset ){
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw += xoffset;
        pitch += yoffset;


        if(pitch > 89.0f )pitch =  89.0f;
        if(pitch < -89.0f)pitch = -89.0f;

        updateCameraVectors();

    }
    void porcessScroll(double yoffset){
            fov -= (float)yoffset;
            if (fov < 1.0f)
                fov = 1.0f;
            if (fov > 45.0f)
                fov = 45.0f; 
    }

    private:
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 f;
        f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        f.y = sin(glm::radians(pitch));
        f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(f);
        // also re-calculate the Right and Up vector
        right = glm::normalize(glm::cross(front, up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        // up    = glm::normalize(glm::cross(right, up));
    }

};

#endif