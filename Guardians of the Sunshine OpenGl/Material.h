#pragma once
#include <glm/glm.hpp>
#include <string>
#include <stb/stb_image.h>
#include <glad/glad.h>
#include "Shader.h"

class Material {
public:
    GLuint diffuseTex;
    GLuint specularTex;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    float alpha = 1;

    Shader* materialShader = nullptr;

    Material(const std::string& diffusePath, const std::string& specularPath, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
    GLuint loadTexture(const std::string& path);
};
