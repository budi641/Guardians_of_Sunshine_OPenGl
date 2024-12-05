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
#include "Camera.h"
#include "InputHandler.h"

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

    Camera camera;

    InputHandler inputHandler;

    world.Deserialize("wolrd.json");

    



    // Transformation matrices
    glm::mat4 view = glm::lookAt(glm::vec3(7.0f, 5.0f, 7.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);





    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = (float)glfwGetTime();
        float deltaTime = 0.016f;

        //view = glm::rotate(view, time * 0.001f, glm::vec3(0, 1, 0));

        
       
        world.GetEntities()[0]->GetTransformComponent()->SetRotation(glm::vec3(0, time * 45, 0));

        shader.Bind();

        shader.SetUniform("u_View", view);
        shader.SetUniform("u_Projection", projection);


        // Bind texture
        texture.Bind(0);
        shader.SetUniform("u_Texture", 0); // Set texture unit

        for (auto entity : world.GetAllEntities())
        {
            shader.SetUniform("u_Model", world.GetWorldMatrix(entity));
            cube.Draw();

        }

        // Swap buffers and check for events

        inputHandler.handleInput(window);
        inputHandler.updateCameraMovement(camera, deltaTime);
        inputHandler.updateCameraRotation(window, camera);

        glm::mat4 view = camera.get_view_matrix();
        //
        glm::mat4 projection = camera.get_projection_matrix(800,600);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
