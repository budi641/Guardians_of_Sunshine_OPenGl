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

class RenderManager {
public:

    GLFWwindow* window;
    float width, height;
    bool enableDepthTest = true;
    bool enableBackFaceCulling = true;

    Light* light;

    Skybox* skybox;
    Camera* camera;



    Shader* shader;


    RenderManager(int width, int height, const char* windowTitle);

    void SetUpOpenGL();

    void Render();


    void EnableDepthTest(bool enable);
    void EnableBackFaceCulling(bool enable);

};
