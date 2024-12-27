#include "Camera.h"
#include <iostream>
#include <glm/glm.hpp>              
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/constants.hpp>     
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "World.h"

Camera::Camera(CameraType type, float width, float height, float fov, float nearPlane, float farPlane, float orthoHeight)
    : type(type), aspectRatio(width / height), fov(fov), nearPlane(nearPlane), farPlane(farPlane), orthoHeight(orthoHeight),
    position(glm::vec3(0.0f, 0.0f, 3.0f)), target(glm::vec3(0.0f, 0.0f, 0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
    yaw(-90.0f), pitch(0.0f)
{
    UpdateCameraVectors();

}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(position, position + target, up);
}

glm::mat4 Camera::GetProjectionMatrix() const {
    return projectionMatrix;
}

void Camera::SetAspectRatio(float width, float height) {
    aspectRatio = width / height;

}

void Camera::UpdateProjection(Shader& shader) {
    if (type == CameraType::Perspective) {
        projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }
    else if (type == CameraType::Orthographic) {
        float halfWidth = orthoHeight * aspectRatio * 0.5f;
        float halfHeight = orthoHeight * 0.5f;
        projectionMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane);
    }

    shader.SetUniform("viewPos", position);
    shader.SetUniform("view", GetViewMatrix());
    shader.SetUniform("projection", projectionMatrix);
}

void Camera::SetYaw(float newYaw) {
    yaw = newYaw;
    if (yaw > 180.0f) yaw -= 360.0f;
    if (yaw < -180.0f) yaw += 360.0f;
    UpdateCameraVectors();
}

void Camera::SetPitch(float newPitch) {
    pitch = newPitch;
    
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
    UpdateCameraVectors();
}

float Camera::GetYaw()
{
    return yaw;
}

float Camera::GetPitch()
{
    return pitch;
}

void Camera::AttachToEntity(Entity* entity, const glm::vec3& offset) {
    attachedEntity = entity;
    this->offset = offset;
}

void Camera::DetachFromEntity() {
    attachedEntity = nullptr;
}

void Camera::UpdateWithEntity() {
    if (attachedEntity) {
    
        glm::vec3 entityPosition = attachedEntity->world->GetWorldPosition(attachedEntity);;
        glm::quat entityRotation = attachedEntity->GetTransformComponent()->GetRotationQuat();

        position = entityPosition + glm::rotate(entityRotation, offset);

        front = glm::normalize(glm::rotate(entityRotation, glm::vec3(0.0f, 0.0f, -1.0f)));
        target = front;

        up = glm::normalize(glm::rotate(entityRotation, glm::vec3(0.0f, 1.0f, 0.0f)));

        right = glm::normalize(glm::cross(front, worldUp));
    }
}



glm::vec3 Camera::GetPosition()
{
    return position;
}

void Camera::SetPosition(glm::vec3 position)
{
    this->position = position;
}

void Camera::SetFov(float newFov) {
   
    fov = newFov;
}

float Camera::GetFov()
{
    return fov;
}

glm::vec3 Camera::GetUp() {
    return up;
}

void Camera::UpdateCameraVectors() {
  

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));


    target = glm::normalize(front);


    right = glm::normalize(glm::cross(worldUp, target));

    
    up = glm::normalize(glm::cross(right, target));

}

