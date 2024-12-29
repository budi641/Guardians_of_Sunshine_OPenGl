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
	meshMaterial->Unbind();
		


}

void SkeletalMeshComponent::PlayIdle()
{
	if (idle)
	{
		animator->PlayAnimation(idle);
	}
}

void SkeletalMeshComponent::PlayRun()
{
	if (Run)
	{
		animator->PlayAnimation(Run);
	}
}

void SkeletalMeshComponent::PlayEmote2()
{
	if (emote2)
	{
		animator->PlayAnimation(emote2);
	}
}

void SkeletalMeshComponent::PlayEmote1()
{
	if (emote1)
	{
		animator->PlayAnimation(emote1);
	}
}

void SkeletalMeshComponent::PlayAttack()
{
	if (attack)
	{
		animator->PlayAnimation(attack);
	}
}

void SkeletalMeshComponent::Update(float deltaTime)
{
	animator->UpdateAnimation(deltaTime);
}
