#pragma once
#include "Vertex.h"
#include <glad/glad.h>
#include <vector>
#include "Shader.h"

class Mesh {
private:
    GLuint vao;       // Vertex Array Object
    GLuint vbo;       // Vertex Buffer Object
    GLuint ebo;       // Element Buffer Object
    size_t indexCount;

public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Bind() const;     // Binds the VAO
    void Unbind() const;   // Unbinds the VAO
    void Draw(const Shader& shader) const;     // Issues the draw call
};
