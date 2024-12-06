#include "RenderManager.h"
#include <iostream>

RenderManager::RenderManager(int width, int height, const char* windowTitle)
    : width(width), height(height) {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        exit(EXIT_FAILURE);  // Terminate the program if GLFW fails
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
        exit(EXIT_FAILURE);  
    }

    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        exit(EXIT_FAILURE); 
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height) {
        glViewport(0, 0, width, height);
        });

    SetUpOpenGL();
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


    glViewport(0, 0, width, height);
}



void RenderManager::Render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    skybox->Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());

    shader->Bind();
    camera->UpdateProjection(*shader);

    glfwSwapBuffers(window);
    glfwPollEvents();

}

void RenderManager::EnableDepthTest(bool enable) {
    if (enable) {
        glEnable(GL_DEPTH_TEST);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }
}

void RenderManager::EnableBackFaceCulling(bool enable) {
    if (enable) {
        glEnable(GL_CULL_FACE);
    }
    else {
        glDisable(GL_CULL_FACE);
    }
}


