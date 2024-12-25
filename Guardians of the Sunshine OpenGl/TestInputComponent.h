#pragma once
#include "InputComponent.h"
class TestInputComponent :
    public InputComponent
{

    void On_W_KeyPressed() override;
    void On_W_KeyReleased() override;
    void On_W_KeyHeld() override;

    void On_S_KeyPressed() override;
    void On_S_KeyReleased() override;
    void On_S_KeyHeld() override;
};

