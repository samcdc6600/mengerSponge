#ifndef CAMERA_HPP_
#define CAMERA_HPP_


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "defs.hpp"


class camera
{
    // ============================ MEMBER VARIABLES ===========================
    // =========================================================================
    const char * FILE_NAME = "camera.hpp";
/*    glm::vec3 cameraPos{};
    glm::vec3 cameraTarget {};
    glm::vec3 cameraDirection {};
    glm::vec3 up {};
    glm::vec3 cameraRight {};
    glm::vec3 cameraUp {};

    glm::mat4 viewMatrix {};*/
    const float camKeyMovSpeed {};

    glm::vec3 camPos {};
    glm::vec3 camFront {}; // AKA target.
    glm::vec3 camUp {};
    /* These values are used to update camFront(what we are looking at).They are
    updated by the mouse position. 
    A yaw of 0.0 would result in a direction vector that points to the right so
    we must rotate to the left. */
    float yaw {-90.0f};
    float pitch {};
  //  float lastX {}, lastY {};
    float camMouseMovSpeed {};

public:
    // ============================ MEMBER FUNCTIONS ===========================
    // =========================================================================
    camera(const glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f),
           const glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f),
           const glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f),
           const float cameraKeyMovSpeed = 0.225f,
           /* We note here that if we capture the mouse with the
           SDL_SetRelativeMouseMode function it's initial position is always
           (0,0). */
    //       const float lastMousePosX = 0.0f,
//           const float lastMousePosY = 0.0f,
           const float cameraMouseMovSpeed = 0.1235f): camPos(cameraPos),
        camFront(cameraFront),
        camUp(cameraUp),
        camKeyMovSpeed(cameraKeyMovSpeed),
  //      lastX(lastMousePosX),
//        lastY(lastMousePosY),
        camMouseMovSpeed(cameraMouseMovSpeed)
    {
    }


/*    void init(const SDL_Window* window)
    {   // Tell GLFW that it should hide and capture the cursor.
    }*/

    void forward(const float timeDelta)
    {
        camPos += camKeyMovSpeed * timeDelta * camFront;
    }


    void backward(const float timeDelta)
    {
        camPos -= camKeyMovSpeed * timeDelta * camFront;
    }


    void left(const float timeDelta)
    {
        camPos -= glm::normalize(glm::cross(camFront, camUp)) *
            camKeyMovSpeed * timeDelta;
    }


    void right(const float timeDelta)
    {
        camPos += glm::normalize(glm::cross(camFront, camUp)) *
            camKeyMovSpeed * timeDelta;
    }


    void updateFront(float x, float y) // This is the TARGET of our affection.
    {
  /*      float xOffset = x - lastX;
        float yOffset = y - lastY;
        lastX = x;
        lastY = y;*/

        x *= camMouseMovSpeed;
        y *= camMouseMovSpeed;
        yaw += x;
        pitch -= y; // We wan't to look up when we move the mouse up!
        // Prevent camera from flipping around when we go past 90 degres :'(.
        if(pitch > 89.5f)
            pitch = 89.5;
        if (pitch < -89.5f)
            pitch = -89.0f;

        camFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        camFront.y = sin(glm::radians(pitch));
        camFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    }


    void updateMatrixs()//glm::vec3 camPos)
    {
     /*   glm::mat4 modelMatrix = glm::mat4(1.0f);
        float rotAngle = 0.0f;

        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotAngle), glm::vec3(0.0f, 0.0f, 1.0f));*/



        // LookAt requires a position, target and up vector.
        glm::mat4 viewMatrix {1};
        // Adding camPos to camFront means that camFront is relative to camPos!
        viewMatrix = glm::lookAt(camPos, camPos + camFront, camUp);
        /*viewMatrix = glm::lookAt(camPos, glm::vec3(0.0, 0.0, 0.0),
                           glm::vec3(0.0, 1.0, 0.0)); */



        glMatrixMode(GL_PROJECTION);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f,
                                                10.0f);

        glPushMatrix();
        glLoadMatrixf(glm::value_ptr(projection));


        // Specifie which matrix stack to use for subsequent matrix operations.
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //glLoadMatrixf(glm::value_ptr(viewMatrix));
        glLoadMatrixf(glm::value_ptr(viewMatrix));
        glPopMatrix();

    }
  
};

#endif