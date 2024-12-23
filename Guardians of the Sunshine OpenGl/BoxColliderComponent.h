#pragma once
#include "Component.h"
#include <reactphysics3d/reactphysics3d.h>


class BoxColliderComponent :
    public Component
{
public:
    reactphysics3d::RigidBody* rigidBody;
    reactphysics3d::Collider* collider;

    BoxColliderComponent();

    void SetUp();

    void Update(float deltaTime) override;

    void Serialize(nlohmann::json& jsonData) const override;
    void Deserialize(const nlohmann::json& jsonData) override;


};

