#include "TransformComponent.h"
#include "Entity.h"
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/quaternion.hpp>        
#include <iostream>
#include <json/json.h>

TransformComponent::TransformComponent(const glm::vec3& initPosition,
    const glm::vec3& initRotation,
    const glm::vec3& initScale)
    : position(initPosition), scale(initScale)
{
    rotation = glm::quat(glm::radians(initRotation));
}

void TransformComponent::Update(float deltaTime) {
    // Update
}

glm::mat4 TransformComponent::GetTransformMatrix() const {
    return glm::translate(glm::mat4(1.0f), position) *
        glm::mat4_cast(rotation) *
        glm::scale(glm::mat4(1.0f), scale);
}

void TransformComponent::Deserialize(const nlohmann::json& jsonData) {
    if (jsonData.contains("position")) {
        position = glm::vec3(
            jsonData["position"][0],
            jsonData["position"][1],
            jsonData["position"][2]
        );
    }

    if (jsonData.contains("rotation")) {
        rotation = glm::quat(glm::radians(glm::vec3(
            jsonData["rotation"][0],
            jsonData["rotation"][1],
            jsonData["rotation"][2]
        )));
    }

    if (jsonData.contains("scale")) {
        scale = glm::vec3(
            jsonData["scale"][0],
            jsonData["scale"][1],
            jsonData["scale"][2]
        );
    }
}

void TransformComponent::SetPosition(const glm::vec3& newPosition) {
    position = newPosition;
}

void TransformComponent::SetRotation(const glm::vec3& eulerAngles) {
    rotation = glm::quat(glm::radians(eulerAngles));
}

void TransformComponent::SetScale(const glm::vec3& newScale) {
    scale = newScale;
}

glm::vec3 TransformComponent::GetPosition() const {
    return position;
}

glm::vec3 TransformComponent::GetRotation() const {
    return glm::degrees(glm::eulerAngles(rotation));
}

glm::vec3 TransformComponent::GetScale() const {
    return scale;
}

std::string TransformComponent::GetComponentName() {
    return this->name;
}

void TransformComponent::SetComponentName(std::string name) {
    this->name = name;
}

std::tuple<glm::vec3, glm::vec3, glm::vec3> TransformComponent::UpdateVectors() {
    return std::make_tuple(rotation * forward, rotation * right, rotation * up);
}
