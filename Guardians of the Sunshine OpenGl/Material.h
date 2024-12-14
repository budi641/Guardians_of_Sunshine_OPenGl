#pragma once
#include <glm/glm.hpp>
#include <string>
#include <stb/stb_image.h>
#include <glad/glad.h>

class Material {
public:
    GLuint diffuseTex;
    GLuint specularTex;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    float alpha = 1;

    Material(const std::string& diffusePath, const std::string& specularPath, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
    GLuint loadTexture(const std::string& path);
};
