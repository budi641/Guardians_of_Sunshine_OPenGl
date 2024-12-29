#include "Collision.h"
#include "SoundManager.h"

void test::onContact(const reactphysics3d::CollisionCallback::CallbackData& callbackData)
{
    for (uint32_t i = 0; i < callbackData.getNbContactPairs(); i++) {
        const auto& contactPair = callbackData.getContactPair(i);

        auto body1 = contactPair.getBody1();
        auto body2 = contactPair.getBody2();

        if (!body1 || !body2) {
            std::cerr << "Null body encountered during collision!" << std::endl;
            continue;
        }

        if (contactPair.getEventType() == reactphysics3d::CollisionCallback::ContactPair::EventType::ContactStart) {
            std::cout << "Collision started between body " << body1 << " and " << body2 << std::endl;
        }
    }
}

void GroundCollisionListener::onContact(const reactphysics3d::CollisionCallback::CallbackData& callbackData)
{
    inAir = true; // Assume the body is in air unless proven otherwise

    for (uint32_t i = 0; i < callbackData.getNbContactPairs(); ++i) {
        const auto& contactPair = callbackData.getContactPair(i);

        // Check contact points for this pair
        for (uint32_t j = 0; j < contactPair.getNbContactPoints(); ++j) {
            const auto& contactPoint = contactPair.getContactPoint(j);

            // Get the contact normal
            reactphysics3d::Vector3 normal = contactPoint.getWorldNormal();

        
            // If the normal is sufficiently "upward," consider the body grounded
            if (normal.y < -0.9f) { // Adjust the threshold based on the steepness tolerance
                inAir = false;
                return; // No need to check further
            }
        }
    }
}

void CustomCollisionListener::onContact(const reactphysics3d::CollisionCallback::CallbackData& callbackData)
{

   

    for (uint32_t i = 0; i < callbackData.getNbContactPairs(); ++i) {
        const auto& contactPair = callbackData.getContactPair(i);

        const auto& collider1 = contactPair.getCollider1();
        const auto& collider2 = contactPair.getCollider2();

        uint32_t category1 = collider1->getCollisionCategoryBits();
        uint32_t category2 = collider2->getCollisionCategoryBits();

        if (category1 == CATEGORY_PLAYER && category2 == CATEGORY_ENEMY)
        {
            reactphysics3d::RigidBody* enemy = dynamic_cast<reactphysics3d::RigidBody*>(collider2->getBody());

            enemy->applyLocalForceAtCenterOfMass(reactphysics3d::Vector3(0, 5000, 0));
            enemy->applyLocalTorque(reactphysics3d::Vector3(0, 5000, 0));
        }
        else if (category1 == CATEGORY_PLAYER && category2 == CATEGORY_COINS) 
        {
            reactphysics3d::RigidBody* coin = dynamic_cast<reactphysics3d::RigidBody*>(collider2->getBody());
         
            coin->applyLocalForceAtCenterOfMass(reactphysics3d::Vector3(0, 5000, 0));
            coin->applyLocalTorque(reactphysics3d::Vector3(0, 5000, 0));
     
            std::cout << "coin" << std::endl;
        }
        else if ((category1 == CATEGORY_PLAYER && category2 == CATEGORY_GROUND) ||
            (category1 == CATEGORY_GROUND && category2 == CATEGORY_PLAYER)) {
            // Handle player-ground collision
        }

        for (uint32_t j = 0; j < contactPair.getNbContactPoints(); ++j) {
            const auto& contactPoint = contactPair.getContactPoint(j);

            // Get the contact point in world space
            const auto& worldPoint = contactPair.getCollider1()->getLocalToWorldTransform() * contactPoint.getLocalPointOnCollider1();

      
        }
    }
}
