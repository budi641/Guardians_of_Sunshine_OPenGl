#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

glm::vec3 Camera::get_position() const {
    return position;
}

void Camera::set_position(const glm::vec3& newPosition) {
    position = newPosition;
}

float Camera::get_pitch() const {
    return pitch;
}

void Camera::set_pitch(float newPitch) {
    pitch = newPitch;
}

float Camera::get_yaw() const {
    return yaw;
}

void Camera::set_yaw(float newYaw) {
    yaw = newYaw;
}

void Camera::set_ortho_height(float height) {
    orthoHeight = height;
}
float Camera::get_ortho_hight()
{
    return orthoHeight;
}
void Camera::set_fovy(float newFovy) {
    fovy = glm::radians(newFovy);
}

float Camera::get_fovy() const {
    return fovy;
}

void Camera::set_zoom(float newZoom) {
    zoom = newZoom;
}

float Camera::get_zoom() const {
    return zoom;
}

glm::vec3 Camera::get_forward() const {
    return glm::vec3(
        cosf(yaw) * cosf(pitch),
        sinf(pitch),
        -sinf(yaw) * cosf(pitch)
    );
}

glm::vec3 Camera::get_right() const {
    return glm::vec3(
        cosf(yaw - glm::half_pi<float>()) * cosf(pitch),
        sinf(pitch),
        -sinf(yaw - glm::half_pi<float>()) * cosf(pitch)
    );
}

glm::mat4 Camera::get_view_matrix() const {
    return glm::lookAt(position, position + get_forward(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::get_projection_matrix(int width, int height) const {
    //
    if (projectionType == ProjectionType::Perspective) {
        return glm::perspective(fovy, float(width) / height, near, far);
    }
    else {
        float aspectRatio = float(width) / height;
        float halfWidth = orthoHeight * aspectRatio * 0.5f;
        return glm::ortho(-halfWidth, halfWidth, -orthoHeight * 0.5f, orthoHeight * 0.5f, near, far);
    }
}

float Camera::get_move_speed()
{
    return moveSpeed;
}
float Camera::get_rotate_speed()
{
    return rotateSpeed;
}
void Camera::set_move_speed(float new_move_speed)
{
    moveSpeed = new_move_speed;
}
void Camera::get_rotate_speed(float new_rotate_speed)
{
    rotateSpeed = new_rotate_speed;
}


void Camera::set_clipping_planes(float nearPlane, float farPlane) {
    near = nearPlane;
    far = farPlane;
}

void Camera::move_forward(float deltaTime) {
    position += get_forward() * moveSpeed * deltaTime;
}

void Camera::move_right(float deltaTime) {
    position += get_right() * moveSpeed * deltaTime;
}

void Camera::move_up(float deltaTime) {
    position.y += moveSpeed * deltaTime;
}

void Camera::move_backward(float deltaTime) {
    position -= get_forward() * moveSpeed * deltaTime;
}

void Camera::move_left(float deltaTime) {
    position -= get_right() * moveSpeed * deltaTime;
}

void Camera::move_down(float deltaTime) {
    position.y -= moveSpeed * deltaTime;
}

void Camera::zoom_in(float deltaTime) {
    fovy -= zoom * deltaTime;

    if (fovy < glm::radians(10.0f)) {
        fovy = glm::radians(10.0f);
    }
}

void Camera::zoom_out(float deltaTime) {
    fovy += zoom * deltaTime;
    if (fovy > glm::radians(45.0f)) {
        fovy = glm::radians(45.0f);
    }
}

void Camera::rotate(float deltaX, float deltaY) {
    //
    yaw += deltaX * rotateSpeed;
    pitch += deltaY * rotateSpeed;

    
    if (pitch > glm::half_pi<float>()) {
        pitch = glm::half_pi<float>();
    }
    else if (pitch < -glm::half_pi<float>()) {
        pitch = -glm::half_pi<float>();
    }
}

void Camera::toggle_projection() {
    if (projectionType == ProjectionType::Perspective) {
        projectionType = ProjectionType::Orthographic;
    }
    else {
        projectionType = ProjectionType::Perspective;
    }
}




