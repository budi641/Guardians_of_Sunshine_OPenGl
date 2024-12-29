#pragma once
#include "Component.h"
#include "reactphysics3d/reactphysics3d.h"
#include "Entity.h"
#include "World.h"
#include "PhysicsManager.h"
#include "Collision.h"

class MovementComponent :
    public Component
{
public:
    MovementComponent(reactphysics3d::RigidBody* body);
    ~MovementComponent() = default;

    void Update(float deltaTime) override;

    void RandomMovement(float deltaTime, float interval, float movementDuration);

    void OnAdd() override;

    void AddForwardMovement(float scale);

    void AddRightMovement(float scale);

    void Jump();

    void Move();

    void StopMovement();

    void UpdateRotationFromDirection();

    void Serialize(nlohmann::json& jsonData) const override {};
    void Deserialize(const nlohmann::json& jsonData) override {};
 
    bool moveRandom = false;

    float speed = 45;

    float maxSpeed = 35;

private:

    reactphysics3d::RigidBody* rigidBody = nullptr;

    reactphysics3d::PhysicsWorld* world;

    GroundCollisionListener* groundListener = nullptr;

    reactphysics3d::Vector3 Direction = reactphysics3d::Vector3(0, 0, 0);



    bool inAir = false;

    float jumpHeight = 750;

};

