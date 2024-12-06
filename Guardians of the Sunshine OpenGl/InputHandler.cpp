#include "InputHandler.h"
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

InputHandler::InputHandler() {}

void InputHandler::handleInput(SDL_Event& event) {
    switch (event.type) {
    case SDL_QUIT:
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.scancode == SDL_SCANCODE_W) inputState.forward = true;
        if (event.key.keysym.scancode == SDL_SCANCODE_S) inputState.back = true;
        if (event.key.keysym.scancode == SDL_SCANCODE_A) inputState.left = true;
        if (event.key.keysym.scancode == SDL_SCANCODE_D) inputState.right = true;
        if (event.key.keysym.scancode == SDL_SCANCODE_Q) inputState.up = true;
        if (event.key.keysym.scancode == SDL_SCANCODE_E) inputState.down = true;
        if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT) inputState.sprint = true;
        if (event.key.keysym.scancode == SDL_SCANCODE_Z) inputState.zoom_in = true;
        if (event.key.keysym.scancode == SDL_SCANCODE_X) inputState.zoom_out = true;
        break;

    case SDL_KEYUP:
        if (event.key.keysym.scancode == SDL_SCANCODE_W) inputState.forward = false;
        if (event.key.keysym.scancode == SDL_SCANCODE_S) inputState.back = false;
        if (event.key.keysym.scancode == SDL_SCANCODE_A) inputState.left = false;
        if (event.key.keysym.scancode == SDL_SCANCODE_D) inputState.right = false;
        if (event.key.keysym.scancode == SDL_SCANCODE_Q) inputState.up = false;
        if (event.key.keysym.scancode == SDL_SCANCODE_E) inputState.down = false;
        if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT) inputState.sprint = false;
        if (event.key.keysym.scancode == SDL_SCANCODE_Z) inputState.zoom_in = false;
        if (event.key.keysym.scancode == SDL_SCANCODE_X) inputState.zoom_out = false;
        break;

    default:
        break;
    }
}

void InputHandler::updateCameraMovement(Camera& camera, float deltaTime) {

    if (inputState.sprint) camera.set_move_speed(camera.get_move_speed() + 1.0f);
    if (inputState.forward) camera.move_forward(deltaTime);
    if (inputState.back) camera.move_backward(deltaTime);
    if (inputState.left) camera.move_left(deltaTime);
    if (inputState.right) camera.move_right(deltaTime);
    if (inputState.up) camera.move_up(deltaTime);
    if (inputState.down) camera.move_down(deltaTime);
    if (inputState.zoom_in) camera.zoom_in(deltaTime);
    if (inputState.zoom_out) camera.zoom_out(deltaTime);
    
}

void InputHandler::updateCameraRotation(Camera& camera) {
    int mouseX, mouseY;
    
    SDL_GetRelativeMouseState(&mouseX, &mouseY);
    
    camera.rotate(mouseX, mouseY);
    
}
