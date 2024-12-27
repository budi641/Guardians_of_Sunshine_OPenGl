#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Material.h"
#include "Vertex.h"  
#include "Shader.h"  
#include "Light.h"

class Mesh {
public:
   
    std::vector<Vertex> vertices; 
    std::vector<unsigned int> indices;  

    GLuint VAO, VBO, EBO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* material);

    void Draw(Shader& shader, const glm::mat4& modelMatrix);

private:

    void setupMesh();
};
