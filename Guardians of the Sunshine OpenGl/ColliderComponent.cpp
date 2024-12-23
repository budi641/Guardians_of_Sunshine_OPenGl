#include "ColliderComponent.h"
#include "Entity.h"
#include "World.h"
#include "PhysicsManager.h"

ColliderComponent::ColliderComponent(float x, float y, float z)
{

	this->size = reactphysics3d::Vector3(x/2,y/2,z/2);

	colliderShape = ColliderShape::Box;
}

ColliderComponent::ColliderComponent(float radius)
{
	this->radius = radius;
	colliderShape = ColliderShape::Sphere;
}

ColliderComponent::ColliderComponent(float radius, float height)
{
	this->radius = radius;
	this->height = height;
	colliderShape = ColliderShape::Capsule;
}

ColliderComponent::~ColliderComponent()
{
	delete collider;
	delete rigidBody;

}

void ColliderComponent::Update(float deltaTime)
{
	
	if (rigidBody)
	{
		reactphysics3d::Transform transform = rigidBody->getTransform();
		parent->GetTransformComponent()->UpdatePhysicsTransform(transform);
	}


}

void ColliderComponent::OnAdd()
{
	rigidBody = parent->world->physicsHandler->CreateRigidBody(parent);

	reactphysics3d::Transform transform = parent->GetEntityPhysicsTransform();

	switch (colliderShape)
	{
		case ColliderShape::Box:

			 collider = rigidBody->addCollider(parent->world->physicsHandler->physicsCommon->createBoxShape(size), transform);

		case ColliderShape::Sphere:

			collider = rigidBody->addCollider(parent->world->physicsHandler->physicsCommon->createSphereShape(radius), transform);

		case ColliderShape::Capsule:

			collider = rigidBody->addCollider(parent->world->physicsHandler->physicsCommon->createCapsuleShape(radius, height), transform);
		default:

			return;
	}


}

void ColliderComponent::Serialize(nlohmann::json& jsonData) const
{
}

void ColliderComponent::Deserialize(const nlohmann::json& jsonData)
{
}
