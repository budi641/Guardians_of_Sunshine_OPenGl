#include "Application.h"
#include "StaticMeshComponent.h"
#include "SkeletalMeshComponent.h"
#include <iostream>
#include "BoxColliderComponent.h"
#include "ColliderComponent.h"


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
    renderer->camera = new Camera(CameraType::Perspective, renderer->width, renderer->height);
    renderer->camera->SetPosition(glm::vec3(0, 7, 10));



    auto* entity = new Entity("Player");
    Material* boxMaterial = new Material("container2.png", "container2_specular.png", glm::vec3(0.0f), glm::vec3(0.3f), glm::vec3(0.2f), 0.4f);
    auto* meshComp = new StaticMeshComponent("", boxMaterial);
    entity->AddComponent(meshComp);
    entity->GetTransformComponent()->SetPosition(glm::vec3(0, 35, 0));
    entity->GetTransformComponent()->SetScale(glm::vec3(3));
    world->AddEntity(entity);

    ColliderComponent* boxCollider = new ColliderComponent(2,4);
    entity->AddComponent(boxCollider);
    boxCollider->rigidBody->setIsDebugEnabled(true);
    boxCollider->rigidBody->setMass(5);
    boxCollider->rigidBody->setAngularLockAxisFactor(reactphysics3d::Vector3(1,1,1));
    boxCollider->collider->getMaterial().setBounciness(1);
    boxCollider->collider->getMaterial().setFrictionCoefficient(1);
    
        

    Entity* floor = new Entity("floor");
    auto* meshFloor = new StaticMeshComponent("", boxMaterial);
    floor->AddComponent(meshFloor);
    floor->GetTransformComponent()->SetPosition(glm::vec3(0, -5, 0));
    floor->GetTransformComponent()->SetScale(glm::vec3(50,0.5 , 50));
    world->AddEntity(floor);
    BoxColliderComponent* floorCollider = new BoxColliderComponent();
    floor->AddComponent(floorCollider);
    floorCollider->SetUp();
    floorCollider->rigidBody->setType(reactphysics3d::BodyType::STATIC);
    floorCollider->rigidBody->setIsDebugEnabled(true);




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



    renderer->light = new Light(glm::vec3(1.0f, 1.0f, 1.0f), 5.0f, glm::vec3(-3.0f, -3.0f, 0.0f));

    world->physicsHandler->EnableDebuging();


    while (!glfwWindowShouldClose(renderer->window) && shouldRun) 
    {
        timer.Update();
        float deltaTime = timer.GetDeltaTime();
        float currentTime = timer.GetCurrentTime();

        inputHandler.handleInput(renderer->window);
        inputHandler.updateCameraMovement(renderer->window, *renderer->camera);

        world->Update(deltaTime);

        renderer->Render(world);

    }

    Quit();
    return;
}

void Application::Quit() 
{
    shouldRun = false;
    glfwTerminate(); 
}
