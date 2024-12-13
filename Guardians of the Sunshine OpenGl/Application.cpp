#include "Application.h"
#include "MeshRenderer.h"
#include "CameraComponent.h"
#include "InputComponent.h"
#include <iostream>

Application::Application(const std::string& path) : worldPath(path)
{
    world = new World();
}

Application::~Application()
{
    delete renderer;
    delete world;
}

void Application::Run()
{
    
    renderer = new RenderManager(1280, 720, "Test App");
    if (!renderer->window)
    {
        return;
    }
    auto* entity = new Entity("Player");

    auto* playerMeshComp = new MeshRenderer("path to model", "container2.png", "container2_specular.png",
        glm::vec3(0.0f), glm::vec3(0.3f), glm::vec3(0.2f), 0.4f);

    entity->AddComponent(playerMeshComp);
    world->AddEntity(entity);
    entity->GetTransformComponent()->SetPosition(glm::vec3(0, 0, 2));

    auto* entity3 = new Entity("Player3");

    auto* playerMeshComp3 = new MeshRenderer("finn1.obj", "finn_texture.png", "",
        glm::vec3(0.0f), glm::vec3(0.3f), glm::vec3(0.2f), 0.4f);

    CameraComponent camera(
        CameraType::Perspective,
        1920.0f, 1080.0f, 45.0f, 0.1f, 100.0f, 0.0f
    );
    camera.SetComponentName("camera");

    InputComponent input(renderer->window);
    input.SetComponentName("input");

    // Add camera, input, and mesh to player entity
    entity3->AddComponent(&camera);
    entity3->AddComponent(&input);
    entity3->AddComponent(playerMeshComp3);
    world->AddEntity(entity3);
    entity3->GetTransformComponent()->SetPosition(glm::vec3(0, 0, 3));

    // Enable back face culling and depth testing in renderer
    renderer->SetBackFaceCulling(true);
    renderer->SetDepthTest(true);

    // Set initial position for the player entity
    entity->GetTransformComponent()->SetPosition(glm::vec3(0, 0, 1));

    // Initialize shaders and skybox
    renderer->shader = new Shader("Vertex_Shader.glsl", "Fragment_Shader.glsl");

    std::vector<std::string> skyCubeMap = {
        "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"
    };
    renderer->skybox = new Skybox(skyCubeMap, "SkySphere_Vertex.glsl", "SkySphere_Fragment.glsl");

    // Set up main camera and light
    renderer->camera = new CameraComponent(CameraType::Perspective, renderer->width, renderer->height);
    renderer->camera->SetPosition(glm::vec3(0, 0, 4));

    renderer->light = new Light(glm::vec3(1.0f, 1.0f, 1.0f), 5.0f, glm::vec3(-3.0f, -3.0f, 0.0f));

    // Main render loop
    while (!glfwWindowShouldClose(renderer->window) && shouldRun)
    {
        // Update the timer and delta time
        timer.Update();
        float deltaTime = timer.GetDeltaTime();
        float currentTime = timer.GetCurrentTime();

        // Handle input and update camera movement and rotation
        input.handleInput();
        input.updateMovement(*entity3->GetTransformComponent());
        input.updateRotation(*entity3->GetTransformComponent());

        // Render scene
        renderer->Render();
        world->RenderWorld(renderer);

        // Update rotation for the player entity based on current time
        entity->GetTransformComponent()->SetRotation(glm::vec3(0, currentTime, currentTime));

        // Swap buffers and poll events
        glfwSwapBuffers(renderer->window);
        glfwPollEvents();

        // Check for OpenGL errors
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cerr << "OpenGL Error: " << error << std::endl;
        }
    }

    Quit();
}

void Application::Quit()
{
    shouldRun = false;
    glfwTerminate();
}
