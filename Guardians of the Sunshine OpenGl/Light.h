#pragma once
#include <glm/glm.hpp>

enum class LightType {
    Directional,
    Point,
    Spot
};

struct Light {
    LightType type;
    glm::vec3 color;
    float intensity;
    glm::vec3 position;   // For Point/Spot light
    glm::vec3 direction;  // For Directional/Spot light

    Light(LightType type, glm::vec3 color, float intensity, glm::vec3 position = {}, glm::vec3 direction = {})
        : type(type), color(color), intensity(intensity), position(position), direction(direction) {}
};
