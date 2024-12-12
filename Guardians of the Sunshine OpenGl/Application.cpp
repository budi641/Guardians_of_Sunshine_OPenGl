#include "Application.h"
#include "StaticMeshComponent.h"
#include "SkeletalMeshComponent.h"
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

    Material* boxMaterial = new Material("container2.png", "container2_specular.png", glm::vec3(0.0f), glm::vec3(0.3f), glm::vec3(0.2f), 0.4f);
    auto* meshComp = new StaticMeshComponent("", boxMaterial);
    entity->AddComponent(meshComp);
    world->AddEntity(entity);
    entity->GetTransformComponent()->SetPosition(glm::vec3(0, 0, 2));


    Material* mat = new Material("", "", glm::vec3(0.0f), glm::vec3(0.3f), glm::vec3(0.2f), 0.4f);
    mat->materialShader = new Shader("animation_vertex.glsl", "animation_fragment.glsl");

    auto* entity2 = new Entity("Player2");
    auto* sKmesh = new SkeletalMeshComponent("Brutal To Happy Walking/Brutal To Happy Walking.dae", mat);
    entity2->AddComponent(sKmesh);
    world->AddEntity(entity2);
    entity2->GetTransformComponent()->SetPosition(glm::vec3(-2, 0, 3));


    auto* entity4 = new Entity("Player2");
    auto* sKmesh2 = new SkeletalMeshComponent("boy/Swing Dancing.dae", mat);
    entity4->AddComponent(sKmesh2);
    world->AddEntity(entity4);
    entity4->GetTransformComponent()->SetPosition(glm::vec3(0, 0, -3));





    auto* entity3 = new Entity("Player3");
    Material* finnMaterial = new Material("finn_texture.png", "",glm::vec3(0.0f), glm::vec3(0.3f), glm::vec3(0.2f), 0.4f);
   auto* meshComp3 = new StaticMeshComponent("finn1.obj", finnMaterial);
    entity3->AddComponent(meshComp3);
    world->AddEntity(entity3);
    entity3->GetTransformComponent()->SetPosition(glm::vec3(5, 0, 4));
    

    renderer->SetBackFaceCulling(true);

    renderer->SetDepthTest(true);



    entity->GetTransformComponent()->SetPosition(glm::vec3(0,0,1));

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

        world->Update(deltaTime);

        renderer->Render();
        world->RenderWorld(renderer);

        entity->GetTransformComponent()->SetRotation(glm::vec3(0, 1*currentTime, 1*currentTime));

        entity3->GetTransformComponent()->SetRotation(glm::vec3(0,30 * currentTime,0));

        glfwSwapBuffers(renderer->window);
        glfwPollEvents();

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL Error: " << error << std::endl;
            std::clearerr;
        }


    }

    Quit();
    return;
}

void Application::Quit() 
{
    shouldRun = false;
    glfwTerminate(); 
}
