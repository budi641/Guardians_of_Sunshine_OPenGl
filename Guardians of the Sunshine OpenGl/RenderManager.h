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
#include "World.h"

class RenderManager {
public:
    GLFWwindow* window = nullptr;
    int width, height;
    bool enableDepthTest = true;
    bool enableBackFaceCulling = false;

    Shader* postProcessShader = nullptr;
    GLuint framebuffer, texture, rbo;
    GLuint quadVAO = 0, quadVBO = 0;

    void SetupQuad();

    std::vector<Light> lights;
    Skybox* skybox = nullptr;
    Camera* camera = nullptr;
    Shader* shader = nullptr;

    RenderManager(int width, int height, const char* windowTitle);
    ~RenderManager();


    void AddLight(const Light& light);
    void SendLightsToShader();

    void SetUpOpenGL();
    void Render(World* world);

    void SetDepthTest(bool enable);
    void SetBackFaceCulling(bool enable);

    void SetUpPostProcessing();
};
