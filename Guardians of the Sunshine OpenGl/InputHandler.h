#pragma once

#include <SDL2/SDL.h>
#include "Camera.h"

struct InputState {
    bool forward = false;
    bool back = false;
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    bool sprint = false;
    bool zoom_in = false;
    bool  zoom_out = false;
};

class InputHandler {


private:
    InputState inputState;
    

public:
    InputHandler();
    void handleInput(SDL_Event& event);  
    void updateCameraMovement(Camera& camera, float deltaTime); 
    void updateCameraRotation(Camera& camera); 


};
