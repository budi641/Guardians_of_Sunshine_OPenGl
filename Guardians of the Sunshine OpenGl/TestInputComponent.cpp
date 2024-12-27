#include "TestInputComponent.h"
#include <iostream>
#include "MovementComponent.h"


void TestInputComponent::Update(float deltaTime)
{
	InputComponent::Update(deltaTime);



}


void TestInputComponent::On_W_KeyPressed()
{
	
}

void TestInputComponent::On_W_KeyReleased()
{
	parent->GetComponentByClass<MovementComponent>()->StopMovement();
}

void TestInputComponent::On_W_KeyHeld()
{
	parent->GetComponentByClass<MovementComponent>()->AddForwardMovement(1);
}

void TestInputComponent::On_S_KeyPressed()
{
	
}

void TestInputComponent::On_S_KeyReleased()
{
	parent->GetComponentByClass<MovementComponent>()->StopMovement();
}

void TestInputComponent::On_S_KeyHeld()
{
	parent->GetComponentByClass<MovementComponent>()->AddForwardMovement(-1);
}
void TestInputComponent::On_A_KeyPressed()
{
	
}
void TestInputComponent::On_A_KeyReleased()
{
	parent->GetComponentByClass<MovementComponent>()->StopMovement();
}
void TestInputComponent::On_D_KeyPressed()
{
	
}
void TestInputComponent::On_D_KeyReleased()
{
	parent->GetComponentByClass<MovementComponent>()->StopMovement();
}
void TestInputComponent::On_D_KeyHeld()
{
	parent->GetComponentByClass<MovementComponent>()->AddRightMovement(1);
}

void TestInputComponent::On_Space_KeyPressed()
{
	parent->GetComponentByClass<MovementComponent>()->Jump();
}

void TestInputComponent::On_A_KeyHeld()
{
	parent->GetComponentByClass<MovementComponent>()->AddRightMovement(-1);
}

void TestInputComponent::On_MouseLeftClickHeld()
{
	
}
