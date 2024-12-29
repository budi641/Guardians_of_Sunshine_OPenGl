#include "CameraComponent.h"
#include "InputComponent.h"

CameraComponent::CameraComponent(CameraType type, float width, float height, float fov, float nearPlane, float farPlane, float orthoHeight)
{
	camera = new Camera(type, width, height, fov, nearPlane, farPlane, orthoHeight);

	arm = new Entity("arm");

	camera->AttachToEntity(arm, glm::vec3(0, 5,30));

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


        glm::vec3 currentRotation = arm->GetTransformComponent()->GetRotation();


        float newXRotation = glm::clamp(currentRotation.x + deltamouse.x, minXRotation, maxXRotation);

        arm->GetTransformComponent()->SetRotation(glm::vec3(newXRotation, currentRotation.y + deltamouse.y, currentRotation.z));
    }
}


void CameraComponent::OnAdd()
{
	parent->AddChild(arm);

	parent->world->renderer->camera = this->camera;
}

void CameraComponent::OnRemove()
{
    parent->RemoveChild(arm);
    parent->world->renderer->camera = nullptr;
}

