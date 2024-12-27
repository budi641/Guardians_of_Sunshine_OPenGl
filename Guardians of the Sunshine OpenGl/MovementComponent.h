#pragma once
#include "Component.h"
#include "reactphysics3d/reactphysics3d.h"
#include "Entity.h"
#include "World.h"
#include "PhysicsManager.h"

class MovementComponent :
    public Component
{
public:
    MovementComponent(reactphysics3d::RigidBody* body);
    ~MovementComponent() = default;

    void Update(float deltaTime) override;

    void OnAdd() override;

    void AddForwardMovement(float scale);

    void AddRightMovement(float scale);

    void Jump();

    void StopMovement();

    void Serialize(nlohmann::json& jsonData) const override {};
    void Deserialize(const nlohmann::json& jsonData) override {};

    void RotateRigidBodyTowardsVelocity();

private:

    reactphysics3d::RigidBody* rigidBody = nullptr;

    reactphysics3d::PhysicsWorld* world;

    reactphysics3d::Quaternion EulerToQuaternion(float pitch, float yaw, float roll);


    bool inAir = false;

    float speed = 50;

    float maxSpeed= 50;

    float jumpHeight = 200;

};

