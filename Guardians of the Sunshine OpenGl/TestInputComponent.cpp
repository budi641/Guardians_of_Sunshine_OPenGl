#include "TestInputComponent.h"
#include <iostream>
#include "MovementComponent.h"
#include "SkeletalMeshComponent.h"
#include "CameraComponent.h"
#include "ColliderComponent.h"


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

void TestInputComponent::On_Shift_Left_KeyPressed()
{
	Entity* finn = parent->world->GetEntityByName("Finn");
	Entity* jake = parent->world->GetEntityByName("Jake");

	if (finn && jake)
	{
		if (isFinn)
		{
			TestInputComponent* inputComp = finn->GetComponentByClass<TestInputComponent>();
			CameraComponent* cameraComp = finn->GetComponentByClass<CameraComponent>();

			finn->RemoveComponent(cameraComp);
			finn->RemoveComponent(inputComp);

			jake->AddComponent(cameraComp);
			jake->AddComponent(inputComp);

			isFinn = false;

		}
		else
		{
			TestInputComponent* inputComp = jake->GetComponentByClass<TestInputComponent>();
			CameraComponent* cameraComp = jake->GetComponentByClass<CameraComponent>();

			jake->RemoveComponent(cameraComp);
			jake->RemoveComponent(inputComp);


			finn->AddComponent(cameraComp);
			finn->AddComponent(inputComp);

			isFinn = true;


		}
	}

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


