#pragma once
#include "Component.h"
#include "reactphysics3d/reactphysics3d.h"


enum class ColliderShape
{
    Box,
    Sphere,
    Capsule,
    ConvexMesh,
    Plane
};

class ColliderComponent :
    public Component
{
public:
    ColliderComponent() = default;
    ColliderComponent(float x, float y, float z);
    ColliderComponent(float radius);
    ColliderComponent(float radius, float height);
    ~ColliderComponent();

    reactphysics3d::RigidBody* rigidBody = nullptr;
    reactphysics3d::Collider* collider = nullptr;

    void Update(float deltaTime) override;
    void OnAdd() override;
    void Serialize(nlohmann::json& jsonData) const override;
    void Deserialize(const nlohmann::json& jsonData) override;

private:
    ColliderShape colliderShape;
    reactphysics3d::Vector3 size;
    float radius;
    float height;
};

