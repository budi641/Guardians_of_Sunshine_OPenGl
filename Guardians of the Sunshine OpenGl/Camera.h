#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include<json/json.h>
using json = nlohmann::json;

enum class CameraType {
    Perspective,
    Orthographic
};

class Camera {
public:
    Camera(CameraType type, float width, float height, float fov = 45.0f,
        float nearPlane = 0.1f, float farPlane = 100.0f, float orthoHeight = 10.0f);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;
    void SetAspectRatio(float width, float height);
    void UpdateProjection(Shader& shader);


    void Serialize(nlohmann::json& jsonData);
    void SetYaw(float newYaw);
    void SetPitch(float newPitch);

    float GetYaw();
    float GetPitch();
    

    void SetFov(float newFov);
    float GetFov();

    glm::vec3 GetUp();

    glm::vec3 GetPosition();

    void SetPosition(glm::vec3 position);

    void SetDef();

    std::tuple<glm::vec3, glm::vec3, glm::vec3> UpdateCameraVectors();

private:
    CameraType type;
    float aspectRatio;
    float fov;           // For Perspective camera
    float def_fov;
    float fov;       
    float nearPlane;
    float farPlane;
    float orthoHeight; 

    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    glm::vec3 def_position;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    float speed = 5.0f;
    float yaw = 0;
    float pitch = 0;
    float def_pitch;
    float def_yaw;


};
