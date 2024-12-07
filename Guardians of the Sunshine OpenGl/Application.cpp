#include "Application.h"
#include "MeshRenderer.h"
#include <iostream>

Application::Application(const std::string& path) : worldPath(path) 
{
    world = new World;
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
    auto* meshComp = new MeshRenderer("path to model", "container2.png", "container2_specular.png",
        glm::vec3(0.0f), glm::vec3(0.3f), glm::vec3(0.2f), 0.4f);
    entity->AddComponent(meshComp);

    renderer->SetBackFaceCulling(true);

    renderer->SetDepthTest(true);


    world->AddEntity(entity);
    entity->GetTransformComponent()->SetScale(glm::vec3(1));

    entity->GetTransformComponent()->SetPosition(glm::vec3(0,0,0));

    renderer->shader = new Shader("Vertex_Shader.glsl", "Fragment_Shader.glsl");

    std::vector<std::string> skyCubeMap = {
    "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"
    };
    renderer->skybox = new Skybox(skyCubeMap, "SkySphere_Vertex.glsl", "SkySphere_Fragment.glsl");

    renderer->camera = new Camera(CameraType::Perspective, renderer->width, renderer->height);
    renderer->camera->SetPosition(glm::vec3(0, 0, 4));

    renderer->light = new Light(glm::vec3(1.0f, 1.0f, 1.0f), 5.0f, glm::vec3(-3.0f, -3.0f, 0.0f));



    while (!glfwWindowShouldClose(renderer->window) && shouldRun) 
    {
        timer.Update();
        float deltaTime = timer.GetDeltaTime();
        float currentTime = timer.GetCurrentTime();


        inputHandler.handleInput(renderer->window);
        inputHandler.updateCameraMovement(renderer->window, *renderer->camera);

        renderer->Render();
        world->RenderWorld(renderer);

        entity->GetTransformComponent()->SetRotation(glm::vec3(0, 1*currentTime, 1*currentTime));


        glfwSwapBuffers(renderer->window);
        glfwPollEvents();

    }

    Quit();
    return;
}

void Application::Quit() 
{
    shouldRun = false;
    glfwTerminate(); 
}
