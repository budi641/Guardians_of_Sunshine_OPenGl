#pragma once
#include "Component.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include "World.h"
#include "RenderManager.h"

class InputComponent : public Component {
public:
    InputComponent();
    InputComponent(GLFWwindow* window);
    ~InputComponent();

    void SetWindow(GLFWwindow* window);

    void OnAdd() override;

    void GetMousePosition(double& xPos, double& yPos) const;

    void Update(float deltaTime) override;

    void Serialize(nlohmann::json& jsonData) const override;
    void Deserialize(const nlohmann::json& jsonData) override;

    virtual void On_A_KeyPressed() {}
    virtual void On_A_KeyReleased() {}
    virtual void On_A_KeyHeld() {}
    virtual void On_B_KeyPressed() {}
    virtual void On_B_KeyReleased() {}
    virtual void On_B_KeyHeld() {}
    virtual void On_C_KeyPressed() {}
    virtual void On_C_KeyReleased() {}
    virtual void On_C_KeyHeld() {}
    virtual void On_D_KeyPressed() {}
    virtual void On_D_KeyReleased() {}
    virtual void On_D_KeyHeld() {}
    virtual void On_E_KeyPressed() {}
    virtual void On_E_KeyReleased() {}
    virtual void On_E_KeyHeld() {}
    virtual void On_F_KeyPressed() {}
    virtual void On_F_KeyReleased() {}
    virtual void On_F_KeyHeld() {}
    virtual void On_G_KeyPressed() {}
    virtual void On_G_KeyReleased() {}
    virtual void On_G_KeyHeld() {}
    virtual void On_H_KeyPressed() {}
    virtual void On_H_KeyReleased() {}
    virtual void On_H_KeyHeld() {}
    virtual void On_I_KeyPressed() {}
    virtual void On_I_KeyReleased() {}
    virtual void On_I_KeyHeld() {}
    virtual void On_J_KeyPressed() {}
    virtual void On_J_KeyReleased() {}
    virtual void On_J_KeyHeld() {}
    virtual void On_K_KeyPressed() {}
    virtual void On_K_KeyReleased() {}
    virtual void On_K_KeyHeld() {}
    virtual void On_L_KeyPressed() {}
    virtual void On_L_KeyReleased() {}
    virtual void On_L_KeyHeld() {}
    virtual void On_M_KeyPressed() {}
    virtual void On_M_KeyReleased() {}
    virtual void On_M_KeyHeld() {}
    virtual void On_N_KeyPressed() {}
    virtual void On_N_KeyReleased() {}
    virtual void On_N_KeyHeld() {}
    virtual void On_O_KeyPressed() {}
    virtual void On_O_KeyReleased() {}
    virtual void On_O_KeyHeld() {}
    virtual void On_P_KeyPressed() {}
    virtual void On_P_KeyReleased() {}
    virtual void On_P_KeyHeld() {}
    virtual void On_Q_KeyPressed() {}
    virtual void On_Q_KeyReleased() {}
    virtual void On_Q_KeyHeld() {}
    virtual void On_R_KeyPressed() {}
    virtual void On_R_KeyReleased() {}
    virtual void On_R_KeyHeld() {}
    virtual void On_S_KeyPressed() {}
    virtual void On_S_KeyReleased() {}
    virtual void On_S_KeyHeld() {}
    virtual void On_T_KeyPressed() {}
    virtual void On_T_KeyReleased() {}
    virtual void On_T_KeyHeld() {}
    virtual void On_U_KeyPressed() {}
    virtual void On_U_KeyReleased() {}
    virtual void On_U_KeyHeld() {}
    virtual void On_V_KeyPressed() {}
    virtual void On_V_KeyReleased() {}
    virtual void On_V_KeyHeld() {}
    virtual void On_W_KeyPressed() {}
    virtual void On_W_KeyReleased() {}
    virtual void On_W_KeyHeld() {}
    virtual void On_X_KeyPressed() {}
    virtual void On_X_KeyReleased() {}
    virtual void On_X_KeyHeld() {}
    virtual void On_Y_KeyPressed() {}
    virtual void On_Y_KeyReleased() {}
    virtual void On_Y_KeyHeld() {}
    virtual void On_Z_KeyPressed() {}
    virtual void On_Z_KeyReleased() {}
    virtual void On_Z_KeyHeld() {}

    virtual void On_0_KeyPressed() {}
    virtual void On_0_KeyReleased() {}
    virtual void On_0_KeyHeld() {}
    virtual void On_1_KeyPressed() {}
    virtual void On_1_KeyReleased() {}
    virtual void On_1_KeyHeld() {}
    virtual void On_2_KeyPressed() {}
    virtual void On_2_KeyReleased() {}
    virtual void On_2_KeyHeld() {}
    virtual void On_3_KeyPressed() {}
    virtual void On_3_KeyReleased() {}
    virtual void On_3_KeyHeld() {}
    virtual void On_4_KeyPressed() {}
    virtual void On_4_KeyReleased() {}
    virtual void On_4_KeyHeld() {}
    virtual void On_5_KeyPressed() {}
    virtual void On_5_KeyReleased() {}
    virtual void On_5_KeyHeld() {}
    virtual void On_6_KeyPressed() {}
    virtual void On_6_KeyReleased() {}
    virtual void On_6_KeyHeld() {}
    virtual void On_7_KeyPressed() {}
    virtual void On_7_KeyReleased() {}
    virtual void On_7_KeyHeld() {}
    virtual void On_8_KeyPressed() {}
    virtual void On_8_KeyReleased() {}
    virtual void On_8_KeyHeld() {}
    virtual void On_9_KeyPressed() {}
    virtual void On_9_KeyReleased() {}
    virtual void On_9_KeyHeld() {}

    virtual void On_Space_KeyPressed() {}
    virtual void On_Space_KeyReleased() {}
    virtual void On_Space_KeyHeld() {}
    virtual void On_Esc_KeyPressed() {}
    virtual void On_Esc_KeyReleased() {}
    virtual void On_Esc_KeyHeld() {}
    virtual void On_Shift_Left_KeyPressed() {}
    virtual void On_Shift_Left_KeyReleased() {}
    virtual void On_Shift_Left_KeyHeld() {}
    virtual void On_Shift_Right_KeyPressed() {}
    virtual void On_Shift_Right_KeyReleased() {}
    virtual void On_Shift_Right_KeyHeld() {}

protected:
    GLFWwindow* window;

private:
    std::unordered_map<int, int> keyStates;

    void CallKeyPressed(int key);
    void CallKeyReleased(int key);
    void CallKeyHeld(int key);
};
