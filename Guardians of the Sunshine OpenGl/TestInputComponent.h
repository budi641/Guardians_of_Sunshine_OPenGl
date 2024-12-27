#pragma once
#include "InputComponent.h"
class TestInputComponent :
    public InputComponent
{
public:

    void Update(float deltaTime) override;

    void On_W_KeyPressed() override;
    void On_W_KeyReleased() override;
    void On_W_KeyHeld() override;

    void On_S_KeyPressed() override;
    void On_S_KeyReleased() override;
    void On_S_KeyHeld() override;

    void On_A_KeyPressed() override;
    void On_A_KeyReleased() override;
    void On_A_KeyHeld() override;

    void On_D_KeyPressed() override;
    void On_D_KeyReleased() override;
    void On_D_KeyHeld() override;

    void On_Space_KeyPressed() override;

    void On_MouseLeftClickHeld() override;
};

