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
        //window = parent->world->renderer->window;
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


void InputComponent::Update(float deltaTime)
{
    if (!window) return;

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
        state = currentState;
    }
}

void InputComponent::Serialize(nlohmann::json& jsonData) const
{
}

void InputComponent::Deserialize(const nlohmann::json& jsonData)
{
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

