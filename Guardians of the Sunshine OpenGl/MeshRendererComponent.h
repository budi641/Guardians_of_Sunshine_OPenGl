#pragma once
#include "Component.h"
#include "Material.h"
#include "Entity.h"
class MeshRendererComponent :
    public Component
{

protected:
    std::string modelPath;

    Material* meshMaterial = nullptr;

public:
    Material* GetMaterial() const;

    virtual void Render(RenderManager* Renderer, glm::mat4 modelMatrix);

    void Serialize(nlohmann::json& jsonData) const override;
    void Deserialize(const nlohmann::json& jsonData) override;

};

