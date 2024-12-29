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
    Animation* idle = nullptr;
    Animation* Run = nullptr;
    Animation* emote1 = nullptr;
    Animation* emote2 = nullptr;
    Animation* attack = nullptr;

    void PlayIdle();
    void PlayRun();
    void PlayAttack();
    void PlayEmote1();
    void PlayEmote2();

    void Update(float deltaTime) override;


};

