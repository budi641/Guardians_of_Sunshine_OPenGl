// RenderManager.cpp
#include "RenderManager.h"
#include <glad/glad.h>
#include <iostream>

RenderManager::RenderManager(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
    int width, int height, const std::string& windowTitle)
    : shader(vertexShaderPath, fragmentShaderPath), width(width), height(height), windowTitle(windowTitle), window(nullptr) {}

RenderManager::~RenderManager() {
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

bool RenderManager::Initialize() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, windowTitle.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return false;
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int newWidth, int newHeight) {
        glViewport(0, 0, newWidth, newHeight);
        });

    glEnable(GL_DEPTH_TEST);
    return true;
}

void RenderManager::AddRenderable(const Mesh& mesh, const Texture& texture) {
    renderables.push_back({ mesh, texture });
}

void RenderManager::SetCameraMatrices(const glm::mat4& view, const glm::mat4& projection) {
    viewMatrix = view;
    projectionMatrix = projection;
}

void RenderManager::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.Bind();
    shader.SetUniform("u_View", viewMatrix);
    shader.SetUniform("u_Projection", projectionMatrix);

    for (const auto& renderable : renderables) {
        renderable.texture.Bind(0);
        shader.SetUniform("u_Texture", 0);
        renderable.mesh.Draw();
    }
}

bool RenderManager::ShouldClose() const {
    return glfwWindowShouldClose(window);
}

void RenderManager::SwapBuffers() const {
    glfwSwapBuffers(window);
}

void RenderManager::PollEvents() const {
    glfwPollEvents();
}
