#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <json/json.h>
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/quaternion.hpp>  

class TransformComponent : public Component
{
private:
    glm::quat rotation;
    glm::vec3 scale;
    glm::vec3 position;


public:
    TransformComponent(const glm::vec3& initPosition = glm::vec3(0.0f),
        const glm::vec3& initRotation = glm::vec3(0.0f),  
        const glm::vec3& initScale = glm::vec3(1.0f));

    void Update(float deltaTime) override;

    glm::mat4 GetTransformMatrix() const;

    void SetPosition(const glm::vec3& newPosition);
    void SetRotation(const glm::vec3& newRotation);
    void SetScale(const glm::vec3& newScale);

    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;
    glm::vec3 GetScale() const;
    void Serialize(nlohmann::json& jsonData) const override {
        jsonData["type"] = "TransformComponent";
        jsonData["position"] = { position.x, position.y, position.z };
        jsonData["rotation"] = { rotation.x, rotation.y, rotation.z };
        jsonData["scale"] = { scale.x, scale.y, scale.z };
    }    void Deserialize(const nlohmann::json& jsonData) override;

};

