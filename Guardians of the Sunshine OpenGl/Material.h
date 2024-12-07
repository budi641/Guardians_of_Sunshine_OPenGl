#pragma once
#include <glm/glm.hpp>
#include <string>
#include <stb/stb_image.h>
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>


//namespace fs = std::filesystem;

class Material {
public:
    GLuint diffuseTex;
    GLuint specularTex;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    float alpha;
    
    std::string TexturesPath;

    Material(const std::string& textureDir);
    GLuint loadTexture(const std::string& path);
    void loadAllTextures();
};
