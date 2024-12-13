#pragma once
#include "Component.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <tuple>
#include <string>

enum class CameraType {
    Perspective,
    Orthographic
};

class CameraComponent : public Component {
public:
    // Camera properties
    CameraType type;
    float aspectRatio;
    float fov;
    float nearPlane;
    float farPlane;
    float orthoHeight;

    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    float yaw, pitch;

    glm::mat4 projectionMatrix;

    // Default camera settings (used for reset)
    glm::vec3 def_position;
    float def_fov;
    float def_yaw;
    float def_pitch;

    CameraComponent(CameraType type, float width, float height, float fov = 45.0f,
        float nearPlane = 0.1f, float farPlane = 100.0f, float orthoHeight = 10.0f);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    void SetAspectRatio(float width, float height);
    void UpdateProjection(Shader& shader);
    void SetYaw(float newYaw);
    float GetYaw();
    void SetPitch(float newPitch);
    float GetPitch();

    glm::vec3 GetPosition() const;
    void SetPosition(glm::vec3 newPosition);

    void SetFov(float newFov);
    float GetFov() const;

    void SetDef();
    std::tuple<glm::vec3, glm::vec3, glm::vec3> UpdateCameraVectors();

    std::string GetComponentName() override;
    void SetComponentName(std::string name) override;

    // Serialize and deserialize camera data
    void Serialize(nlohmann::json& jsonData) const override;
    void Deserialize(const nlohmann::json& jsonData) override;
};


