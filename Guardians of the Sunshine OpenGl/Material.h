#pragma once

#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

class Material {
public:
    Texture* diffuseTexture = nullptr;
    Texture* specularTexture = nullptr;
    Texture* normalTexture = nullptr;

    float alpha = 1.0f;
    float shininess = 32.0f;

    Shader* shader = nullptr;

    Material(float shininess = 0, float alpha = 1.0f,
        const std::string& diffusePath = "", const std::string& specularPath = "",
        const std::string& normalPath = "");

    void Bind(Shader* defaultShader);
    void Unbind() const;
};
