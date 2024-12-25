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
        bool rotate = false;
        bool focus = false;
    };

    InputState inputState;
    float sprint_val = 0.1f;
    float movement_val = 0.05f;

public:

    InputHandler();
   
    void handleInput(GLFWwindow* window);
    void updateCameraMovement(GLFWwindow* window, Camera& camera);
    void updateCameraRotation(GLFWwindow* window, Camera& camera);
};
