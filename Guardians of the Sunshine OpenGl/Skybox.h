#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <stb/stb_image.h>
#include "Shader.h" 

class Skybox {
public:
    Skybox(const std::vector<std::string>& faces, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void Draw(const glm::mat4& view, const glm::mat4& projection);

private:
    GLuint loadCubemap(const std::vector<std::string>& faces); 
    GLuint skyboxVAO, skyboxVBO;
    GLuint cubemapTexture;
    Shader* skyboxShader; 
};
