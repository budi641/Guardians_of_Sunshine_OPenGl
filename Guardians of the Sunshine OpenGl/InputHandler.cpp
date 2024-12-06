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
    inputState.rotate = false;
    inputState.focus = false;
    
    // Check for input keys
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) inputState.forward = true;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) inputState.back = true;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) inputState.left = true;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) inputState.right = true;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) inputState.up = true;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) inputState.down = true;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) inputState.sprint = true;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) inputState.zoom_in = true;
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) inputState.zoom_out = true;
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) inputState.rotate = true;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) inputState.focus = true;

    if(inputState.rotate == false) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}

void InputHandler::updateCameraMovement(GLFWwindow* window, Camera& camera) {
    
    std::tuple<glm::vec3, glm::vec3, glm::vec3> vectors = camera.UpdateCameraVectors();

    float movement_factor = movement_val;
    
    if (inputState.sprint) {
        movement_factor += sprint_val;
    }
    
    // Camera movement 
    
    if (inputState.forward) {
       // glm::vec3 forwardDirection = camera.UpdateCameraVectors(); // Get the forward vector from the camera function
        camera.SetPosition(camera.GetPosition() + std::get<0>(vectors) * movement_factor); // Move the camera in the forward direction
    }


    if (inputState.back) {
        //glm::vec3 forwardDirection = camera.UpdateCameraVectors(); // Get the forward vector from the camera function
        camera.SetPosition(camera.GetPosition() - std::get<0>(vectors) * movement_factor); // Move the camera in the forward direction
    }
   // if (inputState.forward) camera.SetPosition({ camera.UpdateCameraVectors().x, camera.UpdateCameraVectors().y,camera.UpdateCameraVectors().z- movement_factor/2.0 });

    if (inputState.left)
    {
        camera.SetPosition(camera.GetPosition() - std::get<1>(vectors) * movement_factor);
    }
    if (inputState.right)
    {
        camera.SetPosition(camera.GetPosition() + std::get<1>(vectors) * movement_factor);
    }
    if (inputState.up)
    {
        camera.SetPosition(camera.GetPosition() + std::get<2>(vectors) * movement_factor);
    }
    if (inputState.down)
    {
        camera.SetPosition(camera.GetPosition() - std::get<2>(vectors) * movement_factor);
    }
    

    if (inputState.zoom_in) camera.SetFov(abs(camera.GetFov() - movement_factor));
    if (inputState.zoom_out) camera.SetFov(abs(camera.GetFov() + movement_factor));
    if (inputState.rotate) updateCameraRotation( window, camera);


    if (inputState.focus)
    {
        camera.SetDef();

    }

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
    // Set the mouse cursor to be hidden and locked to the center of the window
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    static double lastMouseX = mouseX;
    static double lastMouseY = mouseY;

    double deltaX = mouseX - lastMouseX;
    double deltaY = mouseY - lastMouseY;

    
    const float sensitivity = .3f;

    
    float targetYaw = camera.GetYaw() + deltaX * sensitivity;
    float targetPitch = camera.GetPitch() - deltaY * sensitivity;

    targetPitch = glm::clamp(targetPitch, -89.0f * glm::half_pi<float>(), 89.0f * glm::half_pi<float>());
 
    const float SMOOTHING_FACTOR = .3f; 
    camera.SetYaw(glm::mix(camera.GetYaw(), targetYaw, SMOOTHING_FACTOR));
    camera.SetPitch(glm::mix(camera.GetPitch(), targetPitch, SMOOTHING_FACTOR));

    lastMouseX = mouseX;
    lastMouseY = mouseY;


}

