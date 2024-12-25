#pragma once
#include "InputComponent.h"
class TestInputComponent :
    public InputComponent
{

    void On_W_KeyPressed() override;
    void On_W_KeyReleased() override;

};

