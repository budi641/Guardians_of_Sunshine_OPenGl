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
    Material* material;  

    GLuint VAO, VBO, EBO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* material);

    void Draw(Shader& shader, const glm::mat4& modelMatrix, const glm::vec3& viewPos, const Light& light);

private:

    void setupMesh();
};
