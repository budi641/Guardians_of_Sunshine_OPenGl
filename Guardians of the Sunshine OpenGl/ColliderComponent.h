#pragma once
#include "Component.h"
#include "reactphysics3d/reactphysics3d.h"
#include "Vertex.h"
#include "Collision.h"

enum class ColliderShape
{
    Box,
    Sphere,
    Capsule,
    ConvexMesh,
};

class ColliderComponent :
    public Component
{
public:
    ColliderComponent();
    ColliderComponent(float x, float y, float z);
    ColliderComponent(float radius);
    ColliderComponent(float radius, float height);
    ~ColliderComponent();

    reactphysics3d::RigidBody* rigidBody = nullptr;
    reactphysics3d::Collider* collider = nullptr;

    CustomCollisionListener* collison = nullptr;

    void Update(float deltaTime) override;
    void OnAdd() override;
    void Serialize(nlohmann::json& jsonData) const override;
    void Deserialize(const nlohmann::json& jsonData) override;

private:
    reactphysics3d::ConvexMeshShape* CreateConvexMeshShape(
        const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices);
    ColliderShape colliderShape;
    reactphysics3d::Vector3 size;
    float radius;
    float height;
};

