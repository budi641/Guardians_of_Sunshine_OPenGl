#include "Collision.h"

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