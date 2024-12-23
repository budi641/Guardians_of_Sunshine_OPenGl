#include "BoxColliderComponent.h"
#include "Entity.h"
#include "World.h"
#include <iostream>
#include "PhysicsManager.h"


BoxColliderComponent::BoxColliderComponent()
{
}

void BoxColliderComponent::SetUp()
{
	rigidBody = parent->world->physicsHandler->CreateRigidBody(parent);

	reactphysics3d::Vector3 size(parent->GetTransformComponent()->GetScale().x/2,
		parent->GetTransformComponent()->GetScale().y/2, 
		parent->GetTransformComponent()->GetScale().z/2);

	reactphysics3d::BoxShape* box = parent->world->physicsHandler->physicsCommon->createBoxShape(size);

	reactphysics3d::Transform rpTransform = parent->GetEntityPhysicsTransform();

	collider = rigidBody->addCollider(box, rpTransform);





}

void BoxColliderComponent::Update(float deltaTime)
{

	reactphysics3d::Transform transform = rigidBody->getTransform();

	parent->GetTransformComponent()->UpdatePhysicsTransform(transform);
}

void BoxColliderComponent::Serialize(nlohmann::json& jsonData) const
{
}

void BoxColliderComponent::Deserialize(const nlohmann::json& jsonData)
{
}
