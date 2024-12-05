#include "InputHandler.h"

InputHandler::InputHandler() {}


void InputHandler::handleInput(GLFWwindow* window) {
    
    inputState.forward = inputState.back = inputState.left = inputState.right = false;
    inputState.up = inputState.down = false;
    inputState.sprint = false;
    inputState.zoom_in = inputState.zoom_out = false;

   
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

    if (inputState.sprint) camera.set_move_speed(camera.get_move_speed() + sprint_val);
    if (inputState.forward) camera.move_forward(deltaTime);
    if (inputState.back) camera.move_backward(deltaTime);
    if (inputState.left) camera.move_left(deltaTime);
    if (inputState.right) camera.move_right(deltaTime);
    if (inputState.up) camera.move_up(deltaTime);
    if (inputState.down) camera.move_down(deltaTime);
    if (inputState.zoom_in) camera.zoom_in(deltaTime);
    if (inputState.zoom_out) camera.zoom_out(deltaTime);
}

void InputHandler::updateCameraRotation(GLFWwindow* window, Camera& camera) {
    double mouseX, mouseY;

    
    glfwGetCursorPos(window, &mouseX, &mouseY);

    static double lastMouseX = mouseX;
    static double lastMouseY = mouseY;

    
    double deltaX = mouseX - lastMouseX;
    double deltaY = mouseY - lastMouseY;


    camera.rotate(static_cast<float>(deltaX), static_cast<float>(deltaY));

    lastMouseX = mouseX;
    lastMouseY = mouseY;
}
