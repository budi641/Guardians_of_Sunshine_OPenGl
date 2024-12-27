#include "CameraComponent.h"
#include "InputComponent.h"

CameraComponent::CameraComponent(CameraType type, float width, float height, float fov, float nearPlane, float farPlane, float orthoHeight)
{
	camera = new Camera(type, width, height, fov, nearPlane, farPlane, orthoHeight);

	arm = new Entity("arm");

	camera->AttachToEntity(arm, glm::vec3(0, 5, 15));

	arm->GetTransformComponent()->SetRotation(glm::vec3(-15, 180, 0));


}

CameraComponent::~CameraComponent()
{
	delete camera;
	delete arm;
}

void CameraComponent::Update(float deltaTime)
{
	camera->UpdateWithEntity();

	if (parent->GetComponentByClass<InputComponent>())
	{
		double x;

		double y;

		parent->GetComponentByClass<InputComponent>()->GetMousePosition(x, y);

		glm::vec3 deltamouse = glm::vec3(y, -x, 0);

		arm->GetTransformComponent()->SetRotation(arm->GetTransformComponent()->GetRotation() + deltamouse);
	}

}

void CameraComponent::OnAdd()
{
	parent->AddChild(arm);

	parent->world->renderer->camera = this->camera;
}

