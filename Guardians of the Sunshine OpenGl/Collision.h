#pragma once

#include"iostream"
#include <reactphysics3d/reactphysics3d.h>

class test : public reactphysics3d::EventListener {
    void onContact(const reactphysics3d::CollisionCallback::CallbackData& callbackData) override;

};

class GroundCollisionListener : public reactphysics3d::EventListener {
private:
    bool& inAir;

public:
    GroundCollisionListener(bool& inAirRef) : inAir(inAirRef) {}

    void onContact(const reactphysics3d::CollisionCallback::CallbackData& callbackData) override;
};

class Collision
{


};

