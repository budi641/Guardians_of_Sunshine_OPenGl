#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "World.h"
#include<json/json.h>
#include "Light.h"

// Window dimensions
const GLuint WIDTH = 1280, HEIGHT = 720;

// Set up OpenGL context and load shaders
GLFWwindow* InitOpenGL() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Test", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height) {
        glViewport(0, 0, width, height);
        });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return nullptr;
    }

    glEnable(GL_DEPTH_TEST);  // Enable depth testing for 3D rendering
    return window;
}

// Function to set up a simple cube mesh
Mesh SetupCube() {
    // Vertices for a simple cube
    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},  // 0
        {{ 0.5f, -0.5f, -0.5f}, {.0f, 0.0f}},  // 1
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},  // 2
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},  // 3
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},  // 4
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},  // 5
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},  // 6
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}},  // 7
    };

    std::vector<GLuint> indices = {
        0, 1, 2,  2, 3, 0,  // Front face
        4, 5, 6,  6, 7, 4,  // Back face
        4, 5, 1,  1, 0, 4,  // Bottom face
        7, 6, 2,  2, 3, 7,  // Top face
        4, 0, 3,  3, 7, 4,  // Left face
        1, 5, 6,  6, 2, 1   // Right face
    };

    return Mesh(vertices, indices);
}


// Main function
int main() {
    // Initialize OpenGL and create window
    GLFWwindow* window = InitOpenGL();
    if (!window) return -1;


    // Create and load shaders
    Shader shader("Vertex_Shader.glsl", "Fragment_Shader.glsl");

    // Load texture
    Texture texture("texture.jpg");

    // Set up the cube mesh
    Mesh cube = SetupCube();

    World world;


    world.Deserialize("wolrd.json");




    // Transformation matrices
    glm::mat4 view = glm::lookAt(glm::vec3(7.0f, 5.0f, 7.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    // Define a light
    Light directionalLight(LightType::Directional, glm::vec3(1.0f, 1.0f, 1.0f), 2.0f, {}, glm::vec3(-1.0f, -1.0f, 0.0f));

    GLuint depthMapFBO;
    GLuint depthMap;

    glGenFramebuffers(1, &depthMapFBO);

    // Generate depth texture
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Attach the depth texture to the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);



    // Setup light's view and projection matrix
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 20.0f); // Orthographic projection for directional light
    glm::mat4 lightView = glm::lookAt(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    // Bind depth framebuffer and render the scene
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    shader.Bind();
    shader.SetUniform("u_LightSpaceMatrix", lightSpaceMatrix);

    // Draw the scene (e.g., objects in the scene)
    for (auto entity : world.GetAllEntities()) {
        shader.SetUniform("u_Model", world.GetWorldMatrix(entity));
        cube.Draw();  // or other meshes
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);





    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = (float)glfwGetTime();

        //view = glm::rotate(view, time * 0.001f, glm::vec3(0, 1, 0));

        // Use shader and set uniform values

        world.GetEntities()[0]->GetTransformComponent()->SetRotation(glm::vec3(0, time * 45, 0));

        shader.Bind();

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        shader.SetUniform("u_DepthMap", 1);

        shader.SetUniform("u_View", view);
        shader.SetUniform("u_Projection", projection);
        shader.SetUniform("u_Light.type", static_cast<int>(directionalLight.type));
        shader.SetUniform("u_Light.color", directionalLight.color);
        shader.SetUniform("u_Light.intensity", directionalLight.intensity);
        shader.SetUniform("u_Light.direction", directionalLight.direction);

        // Bind texture
        texture.Bind(0);
        shader.SetUniform("u_Texture", 0); // Set texture unit

        for (auto entity : world.GetAllEntities())
        {
            shader.SetUniform("u_Model", world.GetWorldMatrix(entity));
            cube.Draw();

        }

        // Swap buffers and check for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
