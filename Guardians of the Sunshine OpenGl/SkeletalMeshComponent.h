#pragma once
#include "MeshRendererComponent.h"
#include "Model.h"
#include "Material.h"
#include "Animator.h"
#include "Animation.h"

class SkeletalMeshComponent :
    public MeshRendererComponent
{
private:
    Model* model;
    Animator* animator;
    Animation* animation;
public:
    SkeletalMeshComponent(const std::string& modelPath, Material* material);
    Model* GetModel() const;
    void Render(RenderManager* Renderer, glm::mat4 modelMatrix) override;
    void Update(float deltaTime) override;


};

