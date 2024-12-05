// material.h
#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Texture.h"

class Material {
public:
    glm::vec3 ambient;   // Ambient color
    glm::vec3 diffuse;   // Diffuse color
    glm::vec3 specular;  // Specular color
    unsigned int diffuseTexture;  // Texture path for diffuse map
    unsigned int specularTexture; // Texture path for specular map

    Material(glm::vec3 ambient = glm::vec3(1.0f), glm::vec3 diffuse = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f),
        unsigned int diffuseTexture = 0, unsigned int specularTexture = 0)
        : ambient(ambient), diffuse(diffuse), specular(specular), diffuseTexture(diffuseTexture), specularTexture(specularTexture) {}
};
