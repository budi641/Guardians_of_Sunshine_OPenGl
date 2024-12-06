#include "Camera.h"

Camera::Camera(CameraType type, float width, float height, float fov, float nearPlane, float farPlane, float orthoHeight)
    : type(type), aspectRatio(width / height), fov(fov), nearPlane(nearPlane), farPlane(farPlane), orthoHeight(orthoHeight),
    position(glm::vec3(0.0f, 0.0f, 3.0f)), target(glm::vec3(0.0f, 0.0f, 0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
    yaw(-90.0f), pitch(0.0f)
{
    UpdateCameraVectors();
    def_pitch = pitch;
    def_position = position;
    def_yaw = yaw;
    def_fov = fov;

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

void Camera::SetDef()
{
    pitch = def_pitch;
    yaw = def_yaw;
    position = def_position;
    fov = def_fov;

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
    if (fov > 100.0f) fov=100.0f;
    if (fov < 1.0f) fov = 1.0f;

    
}

float Camera::GetFov()
{
    return fov;
}

glm::vec3 Camera::GetUp() {
    return up;
}

std::tuple<glm::vec3, glm::vec3, glm::vec3> Camera::UpdateCameraVectors() {
  
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    
    front = glm::normalize(front);

 
    glm::vec3 up;
    up.x = sin(glm::radians(yaw) + glm::pi<float>() / 2.0f);
    up.y = 0;  
    up.z = cos(glm::radians(yaw) + glm::pi<float>() / 2.0f);

    // Normalize the right vector
    up = glm::normalize(up);

 
    glm::vec3 right;
    right.x = -sin(glm::radians(pitch)) * sin(glm::radians(yaw));
    //.y = cos(glm::radians(pitch));
    right.z = sin(glm::radians(pitch)) * cos(glm::radians(yaw));
    right.y = 0;


    right = glm::normalize(right);

   
    target = front;


    return std::make_tuple(front, right , up);
}

