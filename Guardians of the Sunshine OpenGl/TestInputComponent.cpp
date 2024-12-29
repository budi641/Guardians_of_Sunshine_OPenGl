#include "TestInputComponent.h"
#include <iostream>
#include "MovementComponent.h"
#include "SkeletalMeshComponent.h"


void TestInputComponent::Update(float deltaTime)
{
	InputComponent::Update(deltaTime);



}


void TestInputComponent::On_W_KeyPressed()
{
	if (!parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()) return;
	parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()->PlayRun();
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
	if (!parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()) return;
	parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()->PlayRun();
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
	if (!parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()) return;
	parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()->PlayRun();
}
void TestInputComponent::On_A_KeyReleased()
{
	parent->GetComponentByClass<MovementComponent>()->StopMovement();
}
void TestInputComponent::On_D_KeyPressed()
{
	if (!parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()) return;
	parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()->PlayRun();
}
void TestInputComponent::On_D_KeyReleased()
{

	parent->GetComponentByClass<MovementComponent>()->StopMovement();
}
void TestInputComponent::On_D_KeyHeld()
{
	parent->GetComponentByClass<MovementComponent>()->AddRightMovement(1);
}

void TestInputComponent::On_Q_KeyPressed()
{
	if (!parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()) return;
	parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()->PlayEmote2();
}

void TestInputComponent::On_E_KeyPressed()
{
	if (!parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()) return;
	parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()->PlayEmote1();
}

void TestInputComponent::On_Space_KeyPressed()
{
	parent->GetComponentByClass<MovementComponent>()->Jump();
}

void TestInputComponent::On_MouseLeftClickPressed()
{
	if (!parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()) return;
	parent->GetChildByName("Mesh")->GetComponentByClass<SkeletalMeshComponent>()->PlayAttack();
}

void TestInputComponent::On_A_KeyHeld()
{
	parent->GetComponentByClass<MovementComponent>()->AddRightMovement(-1);
}


