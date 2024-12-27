#pragma once
#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include <string>
#include <vector>
#include "shader.h"
#include "Vertex.h"

#define MAX_BONE_INFLUENCE 4

//
//struct Texture {
//    unsigned int id;
//    std::string type;
//    std::string path;
//};

class SkeletalMesh {
public:
    // mesh Data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    //std::vector<Texture>      textures;

    unsigned int VAO;

    SkeletalMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices/*, std::vector<Texture> textures*/);

    void Draw(Shader& shader);


private:

    unsigned int VBO, EBO;
    void setupMesh();

};
