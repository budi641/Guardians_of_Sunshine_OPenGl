#include "CameraComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

CameraComponent::CameraComponent(CameraType type, float width, float height, float fov, float nearPlane, float farPlane, float orthoHeight)
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

std::tuple<glm::vec3, glm::vec3, glm::vec3> UpdateCameraVectors();

glm::mat4 CameraComponent::GetViewMatrix() const {
    return glm::lookAt(position, position + target, up);
}

glm::mat4 CameraComponent::GetProjectionMatrix() const {
    return projectionMatrix;
}

void CameraComponent::SetAspectRatio(float width, float height) {
    aspectRatio = width / height;
}

void CameraComponent::UpdateProjection(Shader& shader) {
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

void CameraComponent::SetYaw(float newYaw) {
    yaw = newYaw;
    if (yaw > 180.0f) yaw -= 360.0f;
    if (yaw < -180.0f) yaw += 360.0f;
    UpdateCameraVectors();
}

float CameraComponent::GetYaw()
{
    return yaw;
}

void CameraComponent::SetPitch(float newPitch) {
    pitch = newPitch;
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
    UpdateCameraVectors();
}

float CameraComponent::GetPitch()
{
    return pitch;
}

glm::vec3 CameraComponent::GetPosition() const {
    return position;
}

void CameraComponent::SetPosition(glm::vec3 newPosition) {
    position = newPosition;
}

void CameraComponent::SetFov(float newFov) {
    fov = newFov;
    if (fov > 100.0f) fov = 100.0f;
    if (fov < 1.0f) fov = 1.0f;
}

float CameraComponent::GetFov() const {
    return fov;
}

void CameraComponent::SetDef() {
    position = def_position;
    yaw = def_yaw;
    pitch = def_pitch;
    fov = def_fov;
}

std::tuple<glm::vec3, glm::vec3, glm::vec3> CameraComponent::UpdateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    target = glm::normalize(front);

    glm::vec3 right = glm::normalize(glm::cross(up, target));
    up = glm::normalize(glm::cross(target, right));

    // Now return the tuple
    return std::make_tuple(front, right, up);
}

std::string Component::GetComponentName()
{
    return this->name;
}

void Component::SetComponentName(std::string name)
{
    this->name = name;
}

void CameraComponent::Serialize(nlohmann::json& jsonData) const {
    jsonData["type"] = (type == CameraType::Perspective) ? "Perspective" : "Orthographic";
    jsonData["aspectRatio"] = aspectRatio;
    jsonData["fov"] = fov;
    jsonData["nearPlane"] = nearPlane;
    jsonData["farPlane"] = farPlane;
    jsonData["orthoHeight"] = orthoHeight;
    jsonData["position"] = { position.x, position.y, position.z };
    jsonData["target"] = { target.x, target.y, target.z };
    jsonData["up"] = { up.x, up.y, up.z };
    jsonData["yaw"] = yaw;
    jsonData["pitch"] = pitch;
}

void CameraComponent::Deserialize(const nlohmann::json& jsonData)
{
    //this is a place holder untill we impliment the function
}
