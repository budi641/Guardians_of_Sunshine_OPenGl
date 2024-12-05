#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"

class Skybox {
private:
    unsigned int VAO, VBO, cubemapTexture;
    Shader* shader;

    unsigned int LoadCubemap(const std::string& path);
    void SetupSkybox();

public:
    Skybox(const std::string& cubemapPath, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~Skybox();

    void Render(const glm::mat4& projection, const glm::mat4& view);
};
