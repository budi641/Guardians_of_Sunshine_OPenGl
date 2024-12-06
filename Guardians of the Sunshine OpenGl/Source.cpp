#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Mesh.h"
#include "World.h"
#include "Light.h"
#include "Material.h"
#include "Camera.h"
#include "InputHandler.h"


const GLuint WIDTH = 1280, HEIGHT = 720;


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

std::vector<Vertex> vertices = {
    // Front face
    {{-0.5f, -0.5f,  0.5f}, {}, {0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}}, // Bottom-left
    {{ 0.5f, -0.5f,  0.5f}, {}, {0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}}, // Bottom-right
    {{ 0.5f,  0.5f,  0.5f}, {}, {0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}}, // Top-right
    {{-0.5f,  0.5f,  0.5f}, {}, {0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}}, // Top-left

    // Back face
    {{ 0.5f, -0.5f, -0.5f}, {}, {0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}}, // Bottom-left
    {{-0.5f, -0.5f, -0.5f}, {}, {0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}}, // Bottom-right
    {{-0.5f,  0.5f, -0.5f}, {}, {0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}}, // Top-right
    {{ 0.5f,  0.5f, -0.5f}, {}, {0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}}, // Top-left

    // Left face
    {{-0.5f, -0.5f, -0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // Bottom-left
    {{-0.5f, -0.5f,  0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}}, // Bottom-right
    {{-0.5f,  0.5f,  0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}}, // Top-right
    {{-0.5f,  0.5f, -0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}}, // Top-left

    // Right face
    {{ 0.5f, -0.5f,  0.5f}, {}, {1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // Bottom-left
    {{ 0.5f, -0.5f, -0.5f}, {}, {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}}, // Bottom-right
    {{ 0.5f,  0.5f, -0.5f}, {}, {1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}}, // Top-right
    {{ 0.5f,  0.5f,  0.5f}, {}, {1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}}, // Top-left

    // Top face
    {{-0.5f,  0.5f,  0.5f}, {}, {0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // Bottom-left
    {{ 0.5f,  0.5f,  0.5f}, {}, {0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}}, // Bottom-right
    {{ 0.5f,  0.5f, -0.5f}, {}, {0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}}, // Top-right
    {{-0.5f,  0.5f, -0.5f}, {}, {0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}}, // Top-left

    // Bottom face
    {{-0.5f, -0.5f, -0.5f}, {}, {0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // Bottom-left
    {{ 0.5f, -0.5f, -0.5f}, {}, {0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}}, // Bottom-right
    {{ 0.5f, -0.5f,  0.5f}, {}, {0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}}, // Top-right
    {{-0.5f, -0.5f,  0.5f}, {}, {0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}}, // Top-left
};

std::vector<unsigned int> indices = {
    0, 1, 2, 2, 3, 0,       // Front face
    4, 5, 6, 6, 7, 4,       // Back face
    8, 9, 10, 10, 11, 8,    // Left face
    12, 13, 14, 14, 15, 12, // Right face
    16, 17, 18, 18, 19, 16, // Top face
    20, 21, 22, 22, 23, 20  // Bottom face
};



int main() {
    GLFWwindow* window = InitOpenGL();
    if (!window) return -1;

    Shader shader("Vertex_Shader.glsl", "Fragment_Shader.glsl");

    World world;

    Entity me("name");
    Entity floor("floor");

    world.AddEntity(&floor);

    floor.GetTransformComponent()->SetScale(glm::vec3(10, 0.1, 10));
    floor.GetTransformComponent()->SetPosition(glm::vec3(0, -1, 0));

    world.AddEntity(&me);

    Material material("container2.png", "container2_specular.png", glm::vec3(0.0f), glm::vec3(0.3f), glm::vec3(0.2f), 0.3f);
    Mesh cube(vertices, indices, &material);

    // Create the camera
    Camera camera(CameraType::Perspective, WIDTH, HEIGHT);
    camera.SetPosition(glm::vec3(1, 3, 5));
    camera.SetPitch(-45);

    
    InputHandler inputHandler;

    Light light(glm::vec3(1.0f, 1.0f, 1.0f), 5.0f, glm::vec3(-3.0f, -3.0f, 0.0f));

    while (!glfwWindowShouldClose(window)) {

        float deltaTime = (float)glfwGetTime(); 

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        inputHandler.handleInput(window);  
        inputHandler.updateCameraMovement(window,camera);  
        

        // Rotate the entity over time
        float time = (float)glfwGetTime();
        world.GetEntities()[1]->GetTransformComponent()->SetRotation(glm::vec3(0, time * 45, 0));

        shader.Bind();
        camera.UpdateProjection(shader);

        for (auto entity : world.GetAllEntities()) {
            cube.Draw(shader, world.GetWorldMatrix(entity), camera.GetPosition(), light);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
