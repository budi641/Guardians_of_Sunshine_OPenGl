#include "InputComponent.h"

InputComponent::InputComponent()
{
    keyStates = {
{GLFW_KEY_A, GLFW_RELEASE}, {GLFW_KEY_B, GLFW_RELEASE}, {GLFW_KEY_C, GLFW_RELEASE},
{GLFW_KEY_D, GLFW_RELEASE}, {GLFW_KEY_E, GLFW_RELEASE}, {GLFW_KEY_F, GLFW_RELEASE},
{GLFW_KEY_G, GLFW_RELEASE}, {GLFW_KEY_H, GLFW_RELEASE}, {GLFW_KEY_I, GLFW_RELEASE},
{GLFW_KEY_J, GLFW_RELEASE}, {GLFW_KEY_K, GLFW_RELEASE}, {GLFW_KEY_L, GLFW_RELEASE},
{GLFW_KEY_M, GLFW_RELEASE}, {GLFW_KEY_N, GLFW_RELEASE}, {GLFW_KEY_O, GLFW_RELEASE},
{GLFW_KEY_P, GLFW_RELEASE}, {GLFW_KEY_Q, GLFW_RELEASE}, {GLFW_KEY_R, GLFW_RELEASE},
{GLFW_KEY_S, GLFW_RELEASE}, {GLFW_KEY_T, GLFW_RELEASE}, {GLFW_KEY_U, GLFW_RELEASE},
{GLFW_KEY_V, GLFW_RELEASE}, {GLFW_KEY_W, GLFW_RELEASE}, {GLFW_KEY_X, GLFW_RELEASE},
{GLFW_KEY_Y, GLFW_RELEASE}, {GLFW_KEY_Z, GLFW_RELEASE},

{GLFW_KEY_0, GLFW_RELEASE}, {GLFW_KEY_1, GLFW_RELEASE}, {GLFW_KEY_2, GLFW_RELEASE},
{GLFW_KEY_3, GLFW_RELEASE}, {GLFW_KEY_4, GLFW_RELEASE}, {GLFW_KEY_5, GLFW_RELEASE},
{GLFW_KEY_6, GLFW_RELEASE}, {GLFW_KEY_7, GLFW_RELEASE}, {GLFW_KEY_8, GLFW_RELEASE},
{GLFW_KEY_9, GLFW_RELEASE},

{GLFW_KEY_SPACE, GLFW_RELEASE},
{GLFW_KEY_ESCAPE, GLFW_RELEASE},
{GLFW_KEY_LEFT_SHIFT, GLFW_RELEASE},
{GLFW_KEY_RIGHT_SHIFT, GLFW_RELEASE},
    };
}

InputComponent::InputComponent(GLFWwindow* window) : window(window) {
    keyStates = {
        {GLFW_KEY_A, GLFW_RELEASE}, {GLFW_KEY_B, GLFW_RELEASE}, {GLFW_KEY_C, GLFW_RELEASE},
        {GLFW_KEY_D, GLFW_RELEASE}, {GLFW_KEY_E, GLFW_RELEASE}, {GLFW_KEY_F, GLFW_RELEASE},
        {GLFW_KEY_G, GLFW_RELEASE}, {GLFW_KEY_H, GLFW_RELEASE}, {GLFW_KEY_I, GLFW_RELEASE},
        {GLFW_KEY_J, GLFW_RELEASE}, {GLFW_KEY_K, GLFW_RELEASE}, {GLFW_KEY_L, GLFW_RELEASE},
        {GLFW_KEY_M, GLFW_RELEASE}, {GLFW_KEY_N, GLFW_RELEASE}, {GLFW_KEY_O, GLFW_RELEASE},
        {GLFW_KEY_P, GLFW_RELEASE}, {GLFW_KEY_Q, GLFW_RELEASE}, {GLFW_KEY_R, GLFW_RELEASE},
        {GLFW_KEY_S, GLFW_RELEASE}, {GLFW_KEY_T, GLFW_RELEASE}, {GLFW_KEY_U, GLFW_RELEASE},
        {GLFW_KEY_V, GLFW_RELEASE}, {GLFW_KEY_W, GLFW_RELEASE}, {GLFW_KEY_X, GLFW_RELEASE},
        {GLFW_KEY_Y, GLFW_RELEASE}, {GLFW_KEY_Z, GLFW_RELEASE},

        {GLFW_KEY_0, GLFW_RELEASE}, {GLFW_KEY_1, GLFW_RELEASE}, {GLFW_KEY_2, GLFW_RELEASE},
        {GLFW_KEY_3, GLFW_RELEASE}, {GLFW_KEY_4, GLFW_RELEASE}, {GLFW_KEY_5, GLFW_RELEASE},
        {GLFW_KEY_6, GLFW_RELEASE}, {GLFW_KEY_7, GLFW_RELEASE}, {GLFW_KEY_8, GLFW_RELEASE},
        {GLFW_KEY_9, GLFW_RELEASE},

        {GLFW_KEY_SPACE, GLFW_RELEASE},
        {GLFW_KEY_ESCAPE, GLFW_RELEASE},
        {GLFW_KEY_LEFT_SHIFT, GLFW_RELEASE},
        {GLFW_KEY_RIGHT_SHIFT, GLFW_RELEASE},
    };
}

InputComponent::~InputComponent() = default;

void InputComponent::SetWindow(GLFWwindow* window)
{
    this->window = window;
}

void InputComponent::OnAdd()
{
    if (parent->world)
    {
        window = parent->world->renderer->window;
    }

}

void InputComponent::GetMousePosition(double& xPos, double& yPos) const
{
    if (window)
    {
        glfwGetCursorPos(window, &xPos, &yPos);
    }
    else {
        xPos = yPos = 0.0;
    }
}
void InputComponent::LockCursorToWindow() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void InputComponent::UnlockCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

double InputComponent::GetMouseDeltaX()
{
    return deltaX;
}
double InputComponent::GetMouseDeltaY()
{
    return deltaY;
}

void InputComponent::Update(float deltaTime)
{
    if (!window) return;

    UpdateMouseDelta();

    for (auto& keyState : keyStates) {
        int key = keyState.first;
        int& state = keyState.second;

        int currentState = glfwGetKey(window, key);
        if (currentState == GLFW_PRESS && state != GLFW_PRESS) {
            CallKeyPressed(key);
        }
        else if (currentState == GLFW_RELEASE && state == GLFW_PRESS) {
            CallKeyReleased(key);
        }
        else if (currentState == GLFW_PRESS) {
            CallKeyHeld(key);
        }
        state = currentState;
    }


    int leftState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (leftState == GLFW_PRESS && mouseLeftButtonState != GLFW_PRESS) {
        On_MouseLeftClickPressed();
    }
    else if (leftState == GLFW_RELEASE && mouseLeftButtonState == GLFW_PRESS) {
        On_MouseLeftClickReleased();
    }
    else if (leftState == GLFW_PRESS) {
        On_MouseLeftClickHeld();
    }
    mouseLeftButtonState = leftState;


    int rightState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if (rightState == GLFW_PRESS && mouseRightButtonState != GLFW_PRESS) {
        On_MouseRightClickPressed();
    }
    else if (rightState == GLFW_RELEASE && mouseRightButtonState == GLFW_PRESS) {
        On_MouseRightClickReleased();
    }
    else if (rightState == GLFW_PRESS) {
        On_MouseRightClickHeld();
    }
    mouseRightButtonState = rightState;
}


void InputComponent::Serialize(nlohmann::json& jsonData) const
{
}

void InputComponent::Deserialize(const nlohmann::json& jsonData)
{
}

void InputComponent::UpdateMouseDelta()
{
    double currentMouseX, currentMouseY;
    glfwGetCursorPos(window, &currentMouseX, &currentMouseY);

    if (firstMouseMove) 
    {

        lastMouseX = currentMouseX;
        lastMouseY = currentMouseY;
        firstMouseMove = false;
    }

    deltaX = currentMouseX - lastMouseX;
    deltaY = currentMouseY - lastMouseY;

    lastMouseX = currentMouseX;
    lastMouseY = currentMouseY;


}

void InputComponent::CallKeyPressed(int key) {
    switch (key) {
    case GLFW_KEY_A: On_A_KeyPressed(); break;
    case GLFW_KEY_B: On_B_KeyPressed(); break;
    case GLFW_KEY_C: On_C_KeyPressed(); break;
    case GLFW_KEY_D: On_D_KeyPressed(); break;
    case GLFW_KEY_E: On_E_KeyPressed(); break;
    case GLFW_KEY_F: On_F_KeyPressed(); break;
    case GLFW_KEY_G: On_G_KeyPressed(); break;
    case GLFW_KEY_H: On_H_KeyPressed(); break;
    case GLFW_KEY_I: On_I_KeyPressed(); break;
    case GLFW_KEY_J: On_J_KeyPressed(); break;
    case GLFW_KEY_K: On_K_KeyPressed(); break;
    case GLFW_KEY_L: On_L_KeyPressed(); break;
    case GLFW_KEY_M: On_M_KeyPressed(); break;
    case GLFW_KEY_N: On_N_KeyPressed(); break;
    case GLFW_KEY_O: On_O_KeyPressed(); break;
    case GLFW_KEY_P: On_P_KeyPressed(); break;
    case GLFW_KEY_Q: On_Q_KeyPressed(); break;
    case GLFW_KEY_R: On_R_KeyPressed(); break;
    case GLFW_KEY_S: On_S_KeyPressed(); break;
    case GLFW_KEY_T: On_T_KeyPressed(); break;
    case GLFW_KEY_U: On_U_KeyPressed(); break;
    case GLFW_KEY_V: On_V_KeyPressed(); break;
    case GLFW_KEY_W: On_W_KeyPressed(); break;
    case GLFW_KEY_X: On_X_KeyPressed(); break;
    case GLFW_KEY_Y: On_Y_KeyPressed(); break;
    case GLFW_KEY_Z: On_Z_KeyPressed(); break;

    case GLFW_KEY_0: On_0_KeyPressed(); break;
    case GLFW_KEY_1: On_1_KeyPressed(); break;
    case GLFW_KEY_2: On_2_KeyPressed(); break;
    case GLFW_KEY_3: On_3_KeyPressed(); break;
    case GLFW_KEY_4: On_4_KeyPressed(); break;
    case GLFW_KEY_5: On_5_KeyPressed(); break;
    case GLFW_KEY_6: On_6_KeyPressed(); break;
    case GLFW_KEY_7: On_7_KeyPressed(); break;
    case GLFW_KEY_8: On_8_KeyPressed(); break;
    case GLFW_KEY_9: On_9_KeyPressed(); break;

    case GLFW_KEY_SPACE: On_Space_KeyPressed(); break;
    case GLFW_KEY_ESCAPE: On_Esc_KeyPressed(); break;
    case GLFW_KEY_LEFT_SHIFT: On_Shift_Left_KeyPressed(); break;
    case GLFW_KEY_RIGHT_SHIFT: On_Shift_Right_KeyPressed(); break;
    }
}

void InputComponent::CallKeyReleased(int key) {
    switch (key) {
    case GLFW_KEY_A: On_A_KeyReleased(); break;
    case GLFW_KEY_B: On_B_KeyReleased(); break;
    case GLFW_KEY_C: On_C_KeyReleased(); break;
    case GLFW_KEY_D: On_D_KeyReleased(); break;
    case GLFW_KEY_E: On_E_KeyReleased(); break;
    case GLFW_KEY_F: On_F_KeyReleased(); break;
    case GLFW_KEY_G: On_G_KeyReleased(); break;
    case GLFW_KEY_H: On_H_KeyReleased(); break;
    case GLFW_KEY_I: On_I_KeyReleased(); break;
    case GLFW_KEY_J: On_J_KeyReleased(); break;
    case GLFW_KEY_K: On_K_KeyReleased(); break;
    case GLFW_KEY_L: On_L_KeyReleased(); break;
    case GLFW_KEY_M: On_M_KeyReleased(); break;
    case GLFW_KEY_N: On_N_KeyReleased(); break;
    case GLFW_KEY_O: On_O_KeyReleased(); break;
    case GLFW_KEY_P: On_P_KeyReleased(); break;
    case GLFW_KEY_Q: On_Q_KeyReleased(); break;
    case GLFW_KEY_R: On_R_KeyReleased(); break;
    case GLFW_KEY_S: On_S_KeyReleased(); break;
    case GLFW_KEY_T: On_T_KeyReleased(); break;
    case GLFW_KEY_U: On_U_KeyReleased(); break;
    case GLFW_KEY_V: On_V_KeyReleased(); break;
    case GLFW_KEY_W: On_W_KeyReleased(); break;
    case GLFW_KEY_X: On_X_KeyReleased(); break;
    case GLFW_KEY_Y: On_Y_KeyReleased(); break;
    case GLFW_KEY_Z: On_Z_KeyReleased(); break;

    case GLFW_KEY_0: On_0_KeyReleased(); break;
    case GLFW_KEY_1: On_1_KeyReleased(); break;
    case GLFW_KEY_2: On_2_KeyReleased(); break;
    case GLFW_KEY_3: On_3_KeyReleased(); break;
    case GLFW_KEY_4: On_4_KeyReleased(); break;
    case GLFW_KEY_5: On_5_KeyReleased(); break;
    case GLFW_KEY_6: On_6_KeyReleased(); break;
    case GLFW_KEY_7: On_7_KeyReleased(); break;
    case GLFW_KEY_8: On_8_KeyReleased(); break;
    case GLFW_KEY_9: On_9_KeyReleased(); break;

    case GLFW_KEY_SPACE: On_Space_KeyReleased(); break;
    case GLFW_KEY_ESCAPE: On_Esc_KeyReleased(); break;
    case GLFW_KEY_LEFT_SHIFT: On_Shift_Left_KeyReleased(); break;
    case GLFW_KEY_RIGHT_SHIFT: On_Shift_Right_KeyReleased(); break;
    }
}

void InputComponent::CallKeyHeld(int key) {
    switch (key) {
    case GLFW_KEY_A: On_A_KeyHeld(); break;
    case GLFW_KEY_B: On_B_KeyHeld(); break;
    case GLFW_KEY_C: On_C_KeyHeld(); break;
    case GLFW_KEY_D: On_D_KeyHeld(); break;
    case GLFW_KEY_E: On_E_KeyHeld(); break;
    case GLFW_KEY_F: On_F_KeyHeld(); break;
    case GLFW_KEY_G: On_G_KeyHeld(); break;
    case GLFW_KEY_H: On_H_KeyHeld(); break;
    case GLFW_KEY_I: On_I_KeyHeld(); break;
    case GLFW_KEY_J: On_J_KeyHeld(); break;
    case GLFW_KEY_K: On_K_KeyHeld(); break;
    case GLFW_KEY_L: On_L_KeyHeld(); break;
    case GLFW_KEY_M: On_M_KeyHeld(); break;
    case GLFW_KEY_N: On_N_KeyHeld(); break;
    case GLFW_KEY_O: On_O_KeyHeld(); break;
    case GLFW_KEY_P: On_P_KeyHeld(); break;
    case GLFW_KEY_Q: On_Q_KeyHeld(); break;
    case GLFW_KEY_R: On_R_KeyHeld(); break;
    case GLFW_KEY_S: On_S_KeyHeld(); break;
    case GLFW_KEY_T: On_T_KeyHeld(); break;
    case GLFW_KEY_U: On_U_KeyHeld(); break;
    case GLFW_KEY_V: On_V_KeyHeld(); break;
    case GLFW_KEY_W: On_W_KeyHeld(); break;
    case GLFW_KEY_X: On_X_KeyHeld(); break;
    case GLFW_KEY_Y: On_Y_KeyHeld(); break;
    case GLFW_KEY_Z: On_Z_KeyHeld(); break;

    case GLFW_KEY_0: On_0_KeyHeld(); break;
    case GLFW_KEY_1: On_1_KeyHeld(); break;
    case GLFW_KEY_2: On_2_KeyHeld(); break;
    case GLFW_KEY_3: On_3_KeyHeld(); break;
    case GLFW_KEY_4: On_4_KeyHeld(); break;
    case GLFW_KEY_5: On_5_KeyHeld(); break;
    case GLFW_KEY_6: On_6_KeyHeld(); break;
    case GLFW_KEY_7: On_7_KeyHeld(); break;
    case GLFW_KEY_8: On_8_KeyHeld(); break;
    case GLFW_KEY_9: On_9_KeyHeld(); break;

    case GLFW_KEY_SPACE: On_Space_KeyHeld(); break;
    case GLFW_KEY_ESCAPE: On_Esc_KeyHeld(); break;
    case GLFW_KEY_LEFT_SHIFT: On_Shift_Left_KeyHeld(); break;
    case GLFW_KEY_RIGHT_SHIFT: On_Shift_Right_KeyHeld(); break;
    }
}
