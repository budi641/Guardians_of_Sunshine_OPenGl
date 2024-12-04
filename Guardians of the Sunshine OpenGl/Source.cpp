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
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},  // 1
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

const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    TexCoord = a_TexCoord;
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
}
)";


const char* fragmentShaderSource = R"(
#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
    FragColor = texture(u_Texture, TexCoord);
}
)";

// Main function
int main() {
    // Initialize OpenGL and create window
    GLFWwindow* window = InitOpenGL();
    if (!window) return -1;


    // Create and load shaders
    Shader shader(vertexShaderSource, fragmentShaderSource);

    // Load texture
    Texture texture("texture.jpg");

    // Set up the cube mesh
    Mesh cube = SetupCube();

    World world;

    Entity cube1("cube1");

    Entity cube2("cube2");

    Entity floor("floor");


    world.AddEntity(&cube1);

    world.AddEntity(&cube2);

    world.AddEntity(&floor);

    cube1.AddChild(&cube2);





    // Transformation matrices
    glm::mat4 view = glm::lookAt(glm::vec3(7.0f, 5.0f, 7.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);


    cube1.GetTransformComponent()->SetPosition(glm::vec3(3.0f, -1.0f, 0.0f));

    cube1.GetTransformComponent()->SetScale(glm::vec3(1,1,1));

    cube1.GetTransformComponent()->SetRotation(glm::vec3(0,45,0));

    cube2.GetTransformComponent()->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));

    cube2.GetTransformComponent()->SetScale(glm::vec3(0.3f, 0.3f, 0.3f));

    floor.GetTransformComponent()->SetScale(glm::vec3(50, 50, 0.2));

    floor.GetTransformComponent()->SetPosition(glm::vec3(0, -2, 0));

    floor.GetTransformComponent()->SetRotation(glm::vec3(90, 0, 0));


    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = (float)glfwGetTime();

        view = glm::rotate(view, time * 0.001f, glm::vec3(0, 1, 0));

        // Use shader and set uniform values
        shader.Bind();

        shader.SetUniform("u_View", view);
        shader.SetUniform("u_Projection", projection);

        // Bind texture
        texture.Bind(0);
        shader.SetUniform("u_Texture", 0); // Set texture unit

        for (auto entity : world.GetAllEntities())
        {
            shader.SetUniform("u_Model", world.GetWorldMatrix(entity));
            cube.Draw(shader);

        }

        // Swap buffers and check for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
