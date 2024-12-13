#include "InputComponent.h"
#include <iostream>

InputComponent::InputComponent(GLFWwindow* window) {
    this->window = window;
}

void InputComponent::handleInput() {
    inputState.forward = inputState.back = inputState.left = inputState.right = false;
    inputState.up = inputState.down = false;
    inputState.sprint = false;
    inputState.rotate = false;

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
    std::tuple<glm::vec3, glm::vec3, glm::vec3> vectors = transform.UpdateVectors();
    glm::vec3 position = transform.GetPosition();

    float movement_factor = movement_val;
    if (inputState.sprint) {
        movement_factor += sprint_val;
    }

    if (inputState.forward) {
        position += std::get<0>(vectors) * movement_factor;
    }

    if (inputState.back) {
        position -= std::get<0>(vectors) * movement_factor;
    }

    if (inputState.left) {
        position += std::get<1>(vectors) * movement_factor;
    }

    if (inputState.right) {
        position -= std::get<1>(vectors) * movement_factor;
    }

    if (inputState.up) {
        position += std::get<2>(vectors) * movement_factor;
    }

    if (inputState.down) {
        position -= std::get<2>(vectors) * movement_factor;
    }

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

    rotation.x = glm::clamp(rotation.x, -89.0f, 89.0f);

    transform.SetRotation(rotation);

    lastMouseX = mouseX;
    lastMouseY = mouseY;
}

std::string InputComponent::GetComponentName() {
    return this->name;
}

void InputComponent::SetComponentName(std::string name) {
    this->name = name;
}

void InputComponent::Serialize(nlohmann::json& jsonData) const {
    //emptyyyyy
}

void InputComponent::Deserialize(const nlohmann::json& jsonData) {
    //flippen empty
}
