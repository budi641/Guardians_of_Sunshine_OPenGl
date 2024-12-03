#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include<chrono>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Test", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set viewport
    glViewport(0, 0, 1280, 720);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
        // Positions          // Colors
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // Bottom-left-back
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Bottom-right-back
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // Top-right-back
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // Top-right-back
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  // Top-left-back
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // Bottom-left-back

        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // Bottom-left-front
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Bottom-right-front
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  // Top-right-front
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  // Top-right-front
        -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,  // Top-left-front
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // Bottom-left-front

        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  // Top-left-front
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // Top-left-back
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // Bottom-left-back
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // Bottom-left-back
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // Bottom-left-front
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  // Top-left-front

         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.5f,  // Top-right-front
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Top-right-back
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Bottom-right-back
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Bottom-right-back
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Bottom-right-front
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.5f,  // Top-right-front

        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // Bottom-left-back
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Bottom-right-back
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Bottom-right-front
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Bottom-right-front
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // Bottom-left-front
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // Bottom-left-back

        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  // Top-left-back
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.5f,  // Top-right-back
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.5f,  // Top-right-front
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.5f,  // Top-right-front
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  // Top-left-front
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f   // Top-left-back
    };


    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the VAO and VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute (location 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // Shader source code
    const std::string vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;   // Vertex position
layout(location = 1) in vec3 aColor; // Vertex color
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 fragColor;  // Color to pass to the fragment shader

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    fragColor = aColor;  // Pass color to fragment shader
}

    )";

    const std::string fragmentShaderSource = R"(
#version 330 core
in vec3 fragColor;  // Incoming color from the vertex shader
out vec4 FragColor;

void main()
{
    FragColor = vec4(fragColor, 1.0f);  // Set the color of the fragment
}

    )";

    Shader shader(vertexShaderSource, fragmentShaderSource);

    glm::mat4 modelMatrix = glm::mat4(1.0f);



    // Render loop
    while (!glfwWindowShouldClose(window)) {


        float angle =  0.0f; 
        modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y-axis
        // Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Clear the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(glm::vec3(3.0f, 1.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::perspective(glm::radians(60.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        shader.Bind();
        shader.SetUniform("model", modelMatrix);
        shader.SetUniform("view", view);
        shader.SetUniform("projection", projection);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
