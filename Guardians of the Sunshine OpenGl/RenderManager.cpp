#include "RenderManager.h"
#include <iostream>

RenderManager::RenderManager(int width, int height, const char* windowTitle)
    : width(width), height(height) {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        throw std::runtime_error("GLFW initialization failed");
    }

    // Set GLFW window hints (OpenGL version and profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the GLFW window
    window = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        throw std::runtime_error("GLFW window creation failed");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        throw std::runtime_error("GLAD initialization failed");
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height) {
        glViewport(0, 0, width, height);
        });

    SetUpOpenGL();
}

RenderManager::~RenderManager() {
    delete skybox;
    delete camera;
    delete shader;
    delete light;

    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

void RenderManager::SetUpOpenGL() {
    if (enableDepthTest) {
        glEnable(GL_DEPTH_TEST);

    }

    if (enableBackFaceCulling) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }

    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, width, height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Default background color
}

void RenderManager::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (skybox && camera) {
        skybox->Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
    }

    if (shader) {
        shader->Bind();
    }



}

void RenderManager::SetDepthTest(bool enable) {
    if (enable) {
        glEnable(GL_DEPTH_TEST);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }
    enableDepthTest = enable;
}

void RenderManager::SetBackFaceCulling(bool enable) {
    if (enable) {
        glEnable(GL_CULL_FACE);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }
    else {
        glDisable(GL_CULL_FACE);
    }
    enableBackFaceCulling = enable;
}
