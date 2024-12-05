// RenderManager.h
#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

class RenderManager {
public:
    RenderManager(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        int width, int height, const std::string& windowTitle);
    ~RenderManager();

    bool Initialize();
    void AddRenderable(const Mesh& mesh, const Texture& texture);
    void SetCameraMatrices(const glm::mat4& view, const glm::mat4& projection);
    void Render();
    bool ShouldClose() const;
    void SwapBuffers() const;
    void PollEvents() const;

private:
    GLFWwindow* window;
    int width;
    int height;
    std::string windowTitle;

    Shader shader;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    struct Renderable {
        Mesh mesh;
        Texture texture;
    };

    std::vector<Renderable> renderables;
};
