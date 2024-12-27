#include "SkeletalMeshComponent.h"
#include "RenderManager.h"

SkeletalMeshComponent::SkeletalMeshComponent(const std::string& modelPath, Material* material)
{
	model = new Model(modelPath);
	animation = new Animation(modelPath, model);
	animator = new Animator(animation);

	meshMaterial=material;

}

Model* SkeletalMeshComponent::GetModel() const
{
	return model;
}

void SkeletalMeshComponent::Render(RenderManager* Renderer, glm::mat4 modelMatrix)
{
	meshMaterial->Bind(Renderer->shader);

	if (meshMaterial->shader)
	{
		Renderer->camera->UpdateProjection(*meshMaterial->shader);
		auto transforms = animator->GetFinalBoneMatrices();
		for (int i = 0; i < transforms.size(); ++i)
		{
			meshMaterial->shader->SetUniform("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
		}
		model->Draw(*meshMaterial->shader, modelMatrix);
	}
	else
	{
		Renderer->shader->Bind();
		Renderer->camera->UpdateProjection(*Renderer->shader);
		auto transforms = animator->GetFinalBoneMatrices();
		for (int i = 0; i < transforms.size(); ++i)
		{
			Renderer->shader->SetUniform("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
		}
		model->Draw(*Renderer->shader, modelMatrix);

	}
	
		


}

void SkeletalMeshComponent::Update(float deltaTime)
{
	animator->UpdateAnimation(deltaTime);
}
