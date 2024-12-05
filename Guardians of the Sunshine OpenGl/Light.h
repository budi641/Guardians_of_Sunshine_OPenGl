#pragma once
#include <glm/glm.hpp>

struct Light {
    glm::vec3 color;
    float intensity;
    glm::vec3 direction; 

    Light(glm::vec3 color, float intensity, glm::vec3 direction)
        : color(color), intensity(intensity), direction(direction) {}
};
