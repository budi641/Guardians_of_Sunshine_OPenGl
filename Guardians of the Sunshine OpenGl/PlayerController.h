#pragma once
#include "Component.h"
#include "World.h"
#include "TestInputComponent.h"
#include "CameraComponent.h"
class PlayerController
{
private:
	Entity* player1;
	Entity* player2;
	bool isPlayer1 = true;
	World* world;
	TestInputComponent* input;
	CameraComponent* cameraComponent;
public:
	PlayerController(Entity* p1, Entity* p2,World* w);

	void toggle();
};

