#pragma once
#include <glm/glm.hpp>

// Represents an RGBA color
struct Color {
    float r, g, b, a;

    Color(float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 1.0f)
        : r(red), g(green), b(blue), a(alpha) {}
};


struct Vertex {
    glm::vec3 position; 
    Color color;         
    glm::vec3 normal;    
    glm::vec2 texCoord;  

    Vertex(const glm::vec3& pos, const Color& col, const glm::vec3& norm = glm::vec3(0.0f),
        const glm::vec2& tex = glm::vec2(0.0f))
        : position(pos), color(col), normal(norm), texCoord(tex) {}
};
