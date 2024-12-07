#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Light.h"
#include <glm/glm.hpp>
#include <string>
#include "Entity.h"
#include "World.h"

class MeshRenderer : public Component {
private:
    Mesh* mesh = nullptr;

    std::string modelPath;

public:
    MeshRenderer(const std::string& modelPath,
        const std::string& diffuseTexturePath,
        const std::string& specularTexturePath,
        const glm::vec3& ambient,
        const glm::vec3& diffuse,
        const glm::vec3& specular,
        float shininess);


    Mesh* GetMesh() const;

    Material* GetMaterial() const;

    const std::string& GetModelPath() const;

    const glm::vec3& GetAmbient() const;

    const glm::vec3& GetDiffuse() const;

    const glm::vec3& GetSpecular() const;

    float GetShininess() const;


    void Render(RenderManager* Renderer, glm::mat4 modelMatrix);


    void Serialize(nlohmann::json& jsonData) const override;
    void Deserialize(const nlohmann::json& jsonData) override;

};




