#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <stb/stb_image.h>
#include "Shader.h" 

class Skybox {
public:
    // Constructor takes in shader file paths for vertex and fragment shaders
    Skybox(const std::vector<std::string>& faces, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void Draw(const glm::mat4& view, const glm::mat4& projection);

private:
    GLuint loadCubemap(const std::vector<std::string>& faces); // Load cube map texture from 6 images
    GLuint skyboxVAO, skyboxVBO;
    GLuint cubemapTexture;
    Shader* skyboxShader; 
};
