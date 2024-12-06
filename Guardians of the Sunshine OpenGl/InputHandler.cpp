#include "InputHandler.h"
using namespace std;
#include<iostream>

InputHandler::InputHandler() {}

void InputHandler::handleInput(GLFWwindow* window) {
    // Reset all input states
    inputState.forward = inputState.back = inputState.left = inputState.right = false;
    inputState.up = inputState.down = false;
    inputState.sprint = false;
    inputState.zoom_in = inputState.zoom_out = false;

    // Check for input keys
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) inputState.forward = true;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) inputState.back = true;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) inputState.left = true;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) inputState.right = true;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) inputState.up = true;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) inputState.down = true;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) inputState.sprint = true;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) inputState.zoom_in = true;
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) inputState.zoom_out = true;
}

void InputHandler::updateCameraMovement(Camera& camera, float deltaTime) {
  
    float movement_factor = movement_val;
    if (inputState.sprint) {
        movement_factor += sprint_val;
    }

    // Camera movement
    if (inputState.forward) camera.SetPosition({ camera.GetPosition().x, camera.GetPosition().y,camera.GetPosition().z- movement_factor });
    if (inputState.back) camera.SetPosition({camera.GetPosition().x, camera.GetPosition().y,camera.GetPosition().z+ movement_factor });
    if (inputState.left) camera.SetPosition({ camera.GetPosition().x- movement_factor, camera.GetPosition().y,camera.GetPosition().z });
    if (inputState.right) camera.SetPosition({ camera.GetPosition().x+ movement_factor, camera.GetPosition().y,camera.GetPosition().z });
    if (inputState.up) camera.SetPosition({ camera.GetPosition().x, camera.GetPosition().y+ movement_factor,camera.GetPosition().z });
    if (inputState.down) camera.SetPosition({ camera.GetPosition().x, camera.GetPosition().y- movement_factor,camera.GetPosition().z });

    if (inputState.zoom_in) camera.SetFov(abs(camera.GetFov() - movement_factor));
    if (inputState.zoom_out) camera.SetFov(abs(camera.GetFov() + movement_factor));

    //std::cout << "Camera Position: " << camera.GetPosition().x << ", " << camera.GetPosition().y << ", " << camera.GetPosition().z << std::endl;
    //std::cout << "Camera Fov: " << camera.GetFov();
    //std::cout << "Camera yaw: " << camera.GetYaw();
    /*for (int i = 0; i < 3; i++) {
        std::cout << "viem: ";
        for (int j = 0; j < 3; j++) {
            std::cout << camera.GetViewMatrix()[i][j] <<", ";
        }
        std::cout << std::endl;
    }*/
}



void InputHandler::updateCameraRotation(GLFWwindow* window, Camera& camera) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    static double lastMouseX = mouseX;
    static double lastMouseY = mouseY;

    double deltaX = mouseX - lastMouseX;
    double deltaY = mouseY - lastMouseY;

    
    camera.SetYaw(camera.GetYaw() + deltaX );  
    camera.SetPitch(camera.GetPitch() - deltaY ); 

    lastMouseX = mouseX;
    lastMouseY = mouseY;
}
