#pragma once
#include <glm/glm.hpp>


enum class LightType {
    Directional,
    Point,
    Spotlight
};

struct Light {
    glm::vec3 color;      
    float intensity;      
    glm::vec3 direction;  
    float range;          
    float cutoff;         
    float outerCutoff;   

    LightType type;      


    Light(glm::vec3 color, float intensity, glm::vec3 direction)
        : color(color), intensity(intensity), direction(direction), range(0.0f), cutoff(0.0f), outerCutoff(0.0f), type(LightType::Directional) {}

    Light(glm::vec3 color, float intensity, glm::vec3 position, float range)
        : color(color), intensity(intensity), direction(position), range(range), cutoff(0.0f), outerCutoff(0.0f), type(LightType::Point) {}


    Light(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 direction, float cutoff, float outerCutoff)
        : color(color), intensity(intensity), direction(direction), range(0.0f), cutoff(cutoff), outerCutoff(outerCutoff), type(LightType::Spotlight) {}
};
