#include "MeshRendererComponent.h"

Material* MeshRendererComponent::GetMaterial() const
{
	return meshMaterial;
}

void MeshRendererComponent::Render(RenderManager* Renderer, glm::mat4 modelMatrix)
{
}

void MeshRendererComponent::Serialize(nlohmann::json& jsonData) const
{
}

void MeshRendererComponent::Deserialize(const nlohmann::json& jsonData)
{
}
