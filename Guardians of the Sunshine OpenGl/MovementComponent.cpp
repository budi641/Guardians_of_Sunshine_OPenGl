 #include "MovementComponent.h"
 #include "Entity.h"
#include <cmath>
#include "SkeletalMeshComponent.h"

#include <cstdlib> 
#include <ctime>   


MovementComponent::MovementComponent(reactphysics3d::RigidBody* body)
{
    rigidBody = body;
}
    

void MovementComponent::Update(float deltaTime) {
    if (rigidBody) {
        reactphysics3d::Vector3 velocity = rigidBody->getLinearVelocity();
        float speedSquared = velocity.lengthSquare();

        if (speedSquared > maxSpeed * maxSpeed) {
            velocity = velocity.getUnit() * maxSpeed;
            rigidBody->setLinearVelocity(velocity);
        }


        if (world)
        {
           // world->setEventListener(groundListener);
        }
        
        UpdateRotationFromDirection();
        
    }

    

    if (Direction.x > 1)Direction.x = 1;
    if (Direction.x < -1)Direction.x = -1;
    if (Direction.y > 1)Direction.y = 1;
    if (Direction.y < -1)Direction.y = -1;

    if (Direction.z > 1)Direction.z= 1;
    if (Direction.z < -1)Direction.z = -1;

    if (moveRandom)
    {
        RandomMovement(deltaTime, 1.0f, 2.5f);
    }
    


  // std::cout << Direction.x <<" "<<Direction.y<<" "<<Direction.z<< std::endl;
}


void MovementComponent::RandomMovement(float deltaTime, float interval, float movementDuration) {
    

    static float timer = 0.0f;          
    static bool isMoving = false;       
    static reactphysics3d::Vector3 randomDirection(0.0f, 0.0f, 0.0f);
    timer += deltaTime;

    if (timer >= interval) {
        timer = 0.0f;      
        isMoving = !isMoving; 
    }

    if (!isMoving) {
        StopMovement();
        return;
    }

    static float movementTimer = 0.0f;
    movementTimer += deltaTime;

    if (movementTimer >= movementDuration) {
        movementTimer = 0.0f;

        float randomX = static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f; 
        float randomZ = static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f; 
        randomDirection = reactphysics3d::Vector3(randomX, 0.0f, randomZ).getUnit();
    }

    Direction = randomDirection;
    Move();
}

void MovementComponent::OnAdd()
{
    world = parent->world->physicsHandler->physicsWorld;

    groundListener = new GroundCollisionListener(inAir);

}

void MovementComponent::AddForwardMovement(float scale)
{
    reactphysics3d::Vector3 addDirection(0, 0, scale);
    Direction += addDirection;
    Move();



}

void MovementComponent::Move()
{
    if (rigidBody && !inAir) 
    {
        reactphysics3d::Vector3 forward = reactphysics3d::Vector3(parent->GetTransformComponent()->GetFrontVector().x,
            parent->GetTransformComponent()->GetFrontVector().y,
            parent->GetTransformComponent()->GetFrontVector().z);

        reactphysics3d::Vector3 right = reactphysics3d::Vector3(parent->GetTransformComponent()->GetRightVector().x,
            parent->GetTransformComponent()->GetRightVector().y,
            parent->GetTransformComponent()->GetRightVector().z);

        rigidBody->applyWorldForceAtCenterOfMass(-forward * speed );
    }
}

void MovementComponent::AddRightMovement(float scale)
{
    reactphysics3d::Vector3 addDirection(-scale, 0, 0);
    Direction += addDirection;

    Move();
}



void MovementComponent::Jump()
{
    if (rigidBody && !inAir) {
        reactphysics3d::Vector3 up(0.0f, 1.0f, 0.0f); 
        rigidBody->applyWorldForceAtCenterOfMass(up * jumpHeight);
    }
}

void MovementComponent::StopMovement()
{
    if (rigidBody && !inAir)
    {
        rigidBody->setLinearVelocity(reactphysics3d::Vector3(0.0f, 0.0f, 0.0f));
        rigidBody->setAngularVelocity(reactphysics3d::Vector3(0.0f, 0.0f, 0.0f));

        Direction = reactphysics3d::Vector3(0, 0, 0);
    }

    if (!parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()) return;
    parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()->PlayIdle();

}


void MovementComponent::UpdateRotationFromDirection()
{
    if (rigidBody && !inAir)
    {
        
        reactphysics3d::Vector3 direction = Direction;

        if (direction.x == 0.0f && direction.z == 0.0f)
            return;

        reactphysics3d::Vector3 normalizedDirection = direction;
        normalizedDirection.y = 0.0f; 
        normalizedDirection = normalizedDirection.getUnit();  

        float angle = std::atan2(normalizedDirection.x, normalizedDirection.z); 

        reactphysics3d::Quaternion rotation;

        rotation.setAllValues(0.0f, std::sin(angle / 2.0f), 0.0f, std::cos(angle / 2.0f));

        reactphysics3d::Transform currentTransform = rigidBody->getTransform();

        currentTransform.setOrientation(rotation);

        rigidBody->setTransform(currentTransform);
    }
}



