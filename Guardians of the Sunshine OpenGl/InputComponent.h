#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Component.h"
#include "TransformComponent.h"

class InputComponent : public Component {
private:
    struct InputState {
        bool forward = false;
        bool back = false;
        bool left = false;
        bool right = false;
        bool up = false;
        bool down = false;
        bool sprint = false;
        bool rotate = false;
    };

    InputState inputState;
    float sprint_val = 0.05f;
    float movement_val = 0.05f;
    GLFWwindow* window;

public:
    InputComponent(GLFWwindow* window);
    void handleInput();
    std::string Component::GetComponentName() override;

    void Component::SetComponentName(std::string name) override;

    void updateMovement(TransformComponent& transform);
    void updateRotation(TransformComponent& transform);

    void Serialize(nlohmann::json& jsonData) const override;

    void Deserialize(const nlohmann::json& jsonData) override;

};
