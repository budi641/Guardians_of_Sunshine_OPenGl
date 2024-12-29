#pragma once

#include"iostream"
#include <reactphysics3d/reactphysics3d.h>
#include "Entity.h"


const uint32_t CATEGORY_GROUND = 1 << 0; // 0001
const uint32_t CATEGORY_PLAYER = 1 << 1; // 0010
const uint32_t CATEGORY_ENEMY = 1 << 2;  // 0100
const uint32_t CATEGORY_COINS = 1 << 3;  // 1000


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

class CustomCollisionListener : public reactphysics3d::EventListener {
private:
    Entity* parent;

public:
    CustomCollisionListener(Entity* Parent) : parent(Parent) {}

    void onContact(const reactphysics3d::CollisionCallback::CallbackData& callbackData) override;
};

class Collision
{


};

