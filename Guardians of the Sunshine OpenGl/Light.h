#pragma once
#include <glm/glm.hpp>

#include<json/json.h>
using json = nlohmann::json;
struct Light {
    glm::vec3 color;
    float intensity;
    glm::vec3 direction; 

    Light(glm::vec3 color, float intensity, glm::vec3 direction)
        : color(color), intensity(intensity), direction(direction) {}
    void Serialize(nlohmann::json& jsonData) const {
        // Serialize color (glm::vec3 to array)
        jsonData["color"] = { color.x, color.y, color.z };

        // Serialize intensity
        jsonData["intensity"] = intensity;

        // Serialize direction (glm::vec3 to array)
        jsonData["direction"] = { direction.x, direction.y, direction.z };
    }
};
