#pragma once
#include <glm/glm.hpp>
#include <reactphysics3d/reactphysics3d.h>

#define MAX_BONE_INFLUENCE 4

struct Color {
    float r, g, b, a;

    Color(float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 1.0f)
        : r(red), g(green), b(blue), a(alpha) {}
};

struct DebugVertex
{
    reactphysics3d::Vector3 point;

    DebugVertex(reactphysics3d::Vector3 point)
    {
        this->point = point;

    }

};



struct Vertex {
    glm::vec3 position;
    Color color;
    glm::vec3 normal;
    glm::vec2 texCoord;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    float m_Weights[MAX_BONE_INFLUENCE];

    // Constructor
    Vertex(
        const glm::vec3& position = glm::vec3(0.0f),
        const Color& col = Color(),
        const glm::vec3& normal = glm::vec3(0.0f),
        const glm::vec2& texCoord = glm::vec2(0.0f),
        const glm::vec3& tangent = glm::vec3(0.0f),
        const glm::vec3& bitangent = glm::vec3(0.0f),
        const int boneIDs[MAX_BONE_INFLUENCE] = nullptr,
        const float weights[MAX_BONE_INFLUENCE] = nullptr
    )
        : position(position), color(col), normal(normal), texCoord(texCoord),
        tangent(tangent), bitangent(bitangent)
    {
        if (boneIDs) {
            for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
                m_BoneIDs[i] = boneIDs[i];
            }
        }
        else {
            for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
                m_BoneIDs[i] = -1;
            }
        }

        if (weights) {
            for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
                m_Weights[i] = weights[i];
            }
        }
        else {
            for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
                m_Weights[i] = 0.0f; 
            }
        }
    }
};

