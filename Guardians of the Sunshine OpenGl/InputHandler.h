
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Camera.h"

class InputHandler {



private:
    struct InputState {
        bool forward = false;
        bool back = false;
        bool left = false;
        bool right = false;
        bool up = false;
        bool down = false;
        bool sprint = false;
        bool zoom_in = false;
        bool zoom_out = false;
    };

    InputState inputState;
    float sprint_val = 1.0f;
public:

    InputHandler();
    void handleInput(GLFWwindow* window);

    void updateCameraMovement(Camera& camera, float deltaTime);
    void updateCameraRotation(GLFWwindow* window, Camera& camera);

};


