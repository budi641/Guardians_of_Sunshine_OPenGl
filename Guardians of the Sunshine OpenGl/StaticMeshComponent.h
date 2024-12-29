#pragma once
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Light.h"
#include <glm/glm.hpp>
#include <string>
#include "Entity.h"
#include "World.h"
#include "MeshRendererComponent.h"

class StaticMeshComponent : public MeshRendererComponent {
private:
    Mesh* staticMesh = nullptr;

    std::string modelPath;


    bool LoadOBJ(
        const std::string& filePath,
        std::vector<Vertex>& outVertices,
        std::vector<unsigned int>& outIndices
    );

    std::vector<Vertex> vertices = {

        {{-0.5f, -0.5f,  0.5f}, {}, {0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {}, {0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {}, {0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {}, {0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},

        {{ 0.5f, -0.5f, -0.5f}, {}, {0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {}, {0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {}, {0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {}, {0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}},


        {{-0.5f, -0.5f, -0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},


        {{ 0.5f, -0.5f,  0.5f}, {}, {1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {}, {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {}, {1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {}, {1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},


        {{-0.5f,  0.5f,  0.5f}, {}, {0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {}, {0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {}, {0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {}, {0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}},


        {{-0.5f, -0.5f, -0.5f}, {}, {0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {}, {0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {}, {0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {}, {0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}},
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

public:
    StaticMeshComponent(const std::string& modelPath,Material* material);
    Mesh* GetMesh() const;
    void Render(RenderManager* Renderer, glm::mat4 modelMatrix) override;

    std::vector<unsigned int> GetIndices();
    std::vector<Vertex> GetVertices();
};




