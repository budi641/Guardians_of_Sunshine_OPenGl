#include "Application.h"
#include "MeshRenderer.h"
#include <iostream>

Application::Application(const std::string& path) : worldPath(path) {}

Application::~Application() {
    delete renderer;
    delete world;
}

void Application::Run() {
    renderer = new RenderManager(1270, 720, "Test App");

    if (!renderer->window) {
        std::cerr << "Failed to initialize renderer or window!" << std::endl;
        delete renderer;
        return;
    }

    // Initialize Shader
    renderer->shader = new Shader("Vertex_Shader.glsl", "Fragment_Shader.glsl");

    // Initialize World
    world = new World;

    // Add an entity with a mesh renderer component
    auto* entity = new Entity("Player");
    world->AddEntity(entity);

    auto* meshComp = new MeshRenderer("path to model", "container2.png", "container2_specular.png",
        glm::vec3(0.0f), glm::vec3(0.3f), glm::vec3(0.2f), 0.4f);
    entity->AddComponent(meshComp);

    // Setup Camera
    renderer->camera = new Camera(CameraType::Perspective, renderer->width, renderer->height);
    renderer->camera->SetPosition(glm::vec3(0, 1, 5));

    // Setup Light
    renderer->light = new Light(glm::vec3(1.0f, 1.0f, 1.0f), 5.0f, glm::vec3(-3.0f, -3.0f, 0.0f));

    // Setup Skybox
    std::vector<std::string> skyCubeMap = {
        "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"
    };
    renderer->skybox = new Skybox(skyCubeMap, "SkySphere_Vertex.glsl", "SkySphere_Fragment.glsl");

    // Main loop
    shouldRun = true;
    while (!glfwWindowShouldClose(renderer->window) && shouldRun) {
        renderer->Render(); // Render skybox, camera, and general setup
        world->Render(renderer); // Render entities in the world
    }
    Quit(); // Cleanup when loop ends
}

void Application::Quit() {
    shouldRun = false;
    glfwTerminate(); // Terminate GLFW
}
