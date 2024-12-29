#pragma once
#include "Component.h"
#include "Camera.h"
#include "World.h"
class CameraComponent :
    public Component
{
public:

    CameraComponent(CameraType type, float width, float height, float fov = 45.0f,
        float nearPlane = 0.1f, float farPlane = 500.0f, float orthoHeight = 10.0f);
    ~CameraComponent();

    void Update(float deltaTime)override;

    void OnAdd()override;

    void OnRemove()override;

    void Serialize(nlohmann::json& jsonData) const override {};
    void Deserialize(const nlohmann::json& jsonData) override {};

    Camera* camera;

    Entity* arm;


    float minXRotation = -360;
    float maxXRotation = 360;


};

