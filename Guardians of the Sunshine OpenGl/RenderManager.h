#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "Skybox.h"
#include<json/json.h>
using json = nlohmann::json;

class RenderManager {
public:
    GLFWwindow* window = nullptr;
    int width, height;  // Changed to int for consistency with GLFW
    bool enableDepthTest = true;
    bool enableBackFaceCulling = false;

    Light* light = nullptr;
    Skybox* skybox = nullptr;
    Camera* camera = nullptr;
    Shader* shader = nullptr;

    RenderManager(int width, int height, const char* windowTitle);
    ~RenderManager();

    void SetUpOpenGL();
    void Render();

    void Serialize(nlohmann::json& jsonData) ;
    void SetUpOpenGL();
    void Render();
    void Deserialize(const nlohmann::json& jsonData);  
    void SetDepthTest(bool enable);
    void SetBackFaceCulling(bool enable);
};
