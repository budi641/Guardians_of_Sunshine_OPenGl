#include "InputComponent.h"
#include <iostream>

InputComponent::InputComponent(GLFWwindow* window) {
    this->window = window;
}

void InputComponent::handleInput() {
    // Reset all input states
    inputState.forward = inputState.back = inputState.left = inputState.right = false;
    inputState.up = inputState.down = false;
    inputState.sprint = false;
    inputState.rotate = false;

    // Check for input keys
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) inputState.forward = true;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) inputState.back = true;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) inputState.left = true;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) inputState.right = true;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) inputState.up = true;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) inputState.down = true;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) inputState.sprint = true;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) inputState.rotate = true;
}

void InputComponent::updateMovement(TransformComponent& transform) {
    glm::vec3 position = transform.GetPosition();
    glm::vec3 forward = transform.GetRotation(); // Simplified: assuming forward is based on rotation (you can refine this logic)

    float movement_factor = movement_val;
    if (inputState.sprint) {
        movement_factor += sprint_val;
    }

    // Handle movement based on input state
    if (inputState.forward) {
        position += forward * movement_factor;
    }

    if (inputState.back) {
        position -= forward * movement_factor;
    }

    if (inputState.left) {
        glm::vec3 left = glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)); // Left is cross product of forward and up
        position += left * movement_factor;
    }

    if (inputState.right) {
        glm::vec3 right = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward); // Right is inverse cross product
        position -= right * movement_factor;
    }

    if (inputState.up) {
        position.y += movement_factor;
    }

    if (inputState.down) {
        position.y -= movement_factor;
    }

    // Apply the new position
    transform.SetPosition(position);
}

void InputComponent::updateRotation(TransformComponent& transform) {
    if (!inputState.rotate) return;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    static double lastMouseX = mouseX;
    static double lastMouseY = mouseY;

    double deltaX = mouseX - lastMouseX;
    double deltaY = mouseY - lastMouseY;

    const float sensitivity = 0.1f;

    glm::vec3 rotation = transform.GetRotation();

    rotation.x -= deltaY * sensitivity;
    rotation.y += deltaX * sensitivity;

    // Clamp pitch to prevent flipping
    rotation.x = glm::clamp(rotation.x, -89.0f, 89.0f);

    transform.SetRotation(rotation);

    lastMouseX = mouseX;
    lastMouseY = mouseY;
    
}

std::string InputComponent::GetComponentName()
{
    return this->name;
}

void InputComponent::SetComponentName(std::string name)
{
    this->name = name;
}

void InputComponent::Serialize(nlohmann::json& jsonData) const {
    //emptyyyyy
}

void InputComponent::Deserialize(const nlohmann::json& jsonData)
{
    //this is a place holder untill we impliment the function
}