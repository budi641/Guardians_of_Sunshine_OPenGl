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
        std::vector<unsigned int>& outIndices,
        std::string& texturePath
    );

public:
    StaticMeshComponent(const std::string& modelPath,Material* material);
    Mesh* GetMesh() const;
    void Render(RenderManager* Renderer, glm::mat4 modelMatrix) override;
};




