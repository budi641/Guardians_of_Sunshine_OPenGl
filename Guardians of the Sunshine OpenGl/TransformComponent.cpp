#include "TransformComponent.h"
#include "Entity.h"
#include <glm/gtc/matrix_transform.hpp>  // For matrix transformations
#include <glm/gtc/quaternion.hpp>        // For quaternion math

TransformComponent::TransformComponent(const glm::vec3& initPosition,
    const glm::vec3& initRotation,  // Euler angles in degrees
    const glm::vec3& initScale)
    : position(initPosition), scale(initScale)
{
    // Convert Euler angles (in degrees) to a quaternion
    rotation = glm::quat(glm::radians(initRotation));  // glm::quat takes radians, so we convert from degrees
}

void TransformComponent::Update(float deltaTime)
{
    // Transform-specific update logic could go here, if necessary
    // For example: Update position based on velocity, or rotate over time
}

glm::mat4 TransformComponent::GetTransformMatrix() const
{
    // First, create a translation matrix based on position
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);

    // Apply rotation using the quaternion
    transform *= glm::mat4_cast(rotation);  // Converts quaternion to matrix

    // Apply scaling
    transform = glm::scale(transform, scale);

    return transform;
}



void TransformComponent::SetPosition(const glm::vec3& newPosition)
{
    position = newPosition;
}

void TransformComponent::SetRotation(const glm::vec3& eulerAngles)
{
    // Convert Euler angles (in degrees) to a quaternion
    rotation = glm::quat(glm::radians(eulerAngles));  // Convert to radians before creating the quaternion
}

void TransformComponent::SetScale(const glm::vec3& newScale)
{
    scale = newScale;
}

glm::vec3 TransformComponent::GetPosition() const
{
    return position;
}

glm::vec3 TransformComponent::GetRotation() const
{
    // Convert the quaternion back to Euler angles (in degrees)
    return glm::degrees(glm::eulerAngles(rotation));  // Convert back to degrees from radians
}

glm::vec3 TransformComponent::GetScale() const
{
    return scale;
}
