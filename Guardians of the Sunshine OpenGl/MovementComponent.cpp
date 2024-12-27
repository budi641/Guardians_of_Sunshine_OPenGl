 #include "MovementComponent.h"
 #include "Entity.h"


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


    }
}


void MovementComponent::OnAdd()
{
    world = parent->world->physicsHandler->physicsWorld;
}

void MovementComponent::AddForwardMovement(float scale)
{
    if (rigidBody && !inAir) {
        reactphysics3d::Vector3 forward = reactphysics3d::Vector3(parent->GetTransformComponent()->GetFrontVector().x,
            parent->GetTransformComponent()->GetFrontVector().y,
            parent->GetTransformComponent()->GetFrontVector().z);

        rigidBody->applyWorldForceAtCenterOfMass(forward * -scale * speed);
    }
}

void MovementComponent::AddRightMovement(float scale)
{
    if (rigidBody && !inAir) {
        reactphysics3d::Vector3 right = reactphysics3d::Vector3(parent->GetTransformComponent()->GetRightVector().x,
            parent->GetTransformComponent()->GetRightVector().y,
            parent->GetTransformComponent()->GetRightVector().z);

        rigidBody->applyWorldForceAtCenterOfMass(right * -scale * speed);
    }
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
    if (rigidBody) 
    {
        rigidBody->setLinearVelocity(reactphysics3d::Vector3(0.0f, 0.0f, 0.0f));
        rigidBody->setAngularVelocity(reactphysics3d::Vector3(0.0f, 0.0f, 0.0f));
    }

}



