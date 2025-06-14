#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Entity.h"

enum class CameraType {
    Perspective,
    Orthographic
};

class Camera {
public:
    Camera(CameraType type, float width, float height, float fov = 45.0f,
        float nearPlane = 0.1f, float farPlane = 500.0f, float orthoHeight = 10.0f);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;
    void SetAspectRatio(float width, float height);
    void UpdateProjection(Shader& shader);


    void SetYaw(float newYaw);
    void SetPitch(float newPitch);

    float GetYaw();
    float GetPitch();
    

    void SetFov(float newFov);
    float GetFov();

    glm::vec3 GetUp();

    glm::vec3 GetPosition();

    void SetPosition(glm::vec3 position);

    void UpdateCameraVectors();

    void AttachToEntity(Entity* entity, const glm::vec3& offset);
    void DetachFromEntity();
    void UpdateWithEntity();

    glm::vec3 front;
    glm::vec3 right;

    Entity* attachedEntity = nullptr;

private:
    CameraType type;

    float aspectRatio;
    float fov;           
    float nearPlane;
    float farPlane;
    float orthoHeight; 

    glm::vec3 worldUp = { 0,-1,0 };

    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    float yaw = 0;
    float pitch = 0;


    glm::vec3 offset;

};
