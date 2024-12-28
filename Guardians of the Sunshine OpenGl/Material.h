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

    GLenum blendSrcFactor = GL_SRC_ALPHA;
    GLenum blendDstFactor = GL_ONE_MINUS_SRC_ALPHA;
    bool enableBlend = false;


    bool enableBackFaceCulling = true;
    GLenum cullFace = GL_BACK;

    Material(float shininess = 0, float alpha = 1.0f,
        const std::string& diffusePath = "", const std::string& specularPath = "",
        const std::string& normalPath = "");

    void Bind(Shader* defaultShader);
    void Unbind() const;

    void SetBlendMode(GLenum srcFactor, GLenum dstFactor);
    void SetBackFaceCulling(bool enable, GLenum face = GL_BACK);
};
