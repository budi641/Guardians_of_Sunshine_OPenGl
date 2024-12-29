#include "PlayerController.h"

PlayerController::PlayerController(Entity* p1, Entity* p2,World* w)
{
	player1 = p1;
	player2 = p2;
	world = w;

	CameraComponent* cameraComponent = new CameraComponent(CameraType::Perspective, world->renderer->width, world->renderer->height);
	TestInputComponent* input = new TestInputComponent();
	input->SetWindow(world->renderer->window);
	input->LockCursorToWindow();

	player1->AddComponent(cameraComponent);
	player1->AddComponent(input);

}

void PlayerController::toggle()
{
	if (isPlayer1)
	{
		player1->RemoveComponent(cameraComponent);
		player1->RemoveComponent(input);

		player2->AddComponent(cameraComponent);
		player2->AddComponent(input);

		isPlayer1 = false;
	}
	else
	{
		player2->RemoveComponent(cameraComponent);
		player2->RemoveComponent(input);

		player1->AddComponent(cameraComponent);
		player1->AddComponent(input);

		isPlayer1 = true;
	}

}
