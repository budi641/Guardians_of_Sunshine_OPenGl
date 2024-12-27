#include "Application.h"
#include "StaticMeshComponent.h"
#include "SkeletalMeshComponent.h"
#include <iostream>
#include "ColliderComponent.h"
#include "TestInputComponent.h"
#include "CameraComponent.h"
#include "MovementComponent.h"


Application::Application(const std::string& path) : worldPath(path) 
{
    world = new World;
    renderer = new RenderManager(1280, 720, "Test App");
    world->renderer = this->renderer;
}

Application::~Application() 
{
    delete renderer;
    delete world;
}

void Application::Run() 
{

    if (!renderer->window) 
    {
        return;
    }



    auto* entity = new Entity("Player");
    Material* boxMaterial = new Material(5,1,"container2.png", "container2_specular.png","");
    auto* meshComp = new StaticMeshComponent("", boxMaterial);
    entity->AddComponent(meshComp);
    entity->GetTransformComponent()->SetPosition(glm::vec3(0, 0, 0));
    entity->GetTransformComponent()->SetScale(glm::vec3(3));
    world->AddEntity(entity);



    
        

    Entity* floor = new Entity("floor");
    auto* meshFloor = new StaticMeshComponent("", boxMaterial);
    floor->AddComponent(meshFloor);
    floor->GetTransformComponent()->SetPosition(glm::vec3(0, -2, 0));
    floor->GetTransformComponent()->SetScale(glm::vec3(500,0.5 , 500));
    world->AddEntity(floor);
    ColliderComponent* floorCollider = new ColliderComponent(500,0.5,500);
    floor->AddComponent(floorCollider);
    floorCollider->rigidBody->setType(reactphysics3d::BodyType::STATIC);
    floorCollider->rigidBody->setIsDebugEnabled(true);




    Material* mat = new Material(15,1,"Brutal To Happy Walking/textures/vanguard_diffuse1.png", 
        "Brutal To Happy Walking/textures/vanguard_specular.png",
        "Brutal To Happy Walking/textures/vanguard_normal.png");
    auto* entity2 = new Entity("Player2");
    auto* sKmesh = new SkeletalMeshComponent("Brutal To Happy Walking/Brutal To Happy Walking.dae", mat);
    entity2->AddComponent(sKmesh);
    world->AddEntity(entity2);
    entity2->GetTransformComponent()->SetPosition(glm::vec3(-4, -2, 3));


    entity2->GetTransformComponent()->SetScale(glm::vec3(4));





    auto* entity3 = new Entity("Player3");
    Material* finnMaterial = new Material(0,1,"finn_texture.png","","");
   auto* meshComp3 = new StaticMeshComponent("finn1.obj", finnMaterial);
    entity3->AddComponent(meshComp3);
    world->AddEntity(entity3);
    entity3->GetTransformComponent()->SetPosition(glm::vec3(5, 2, 4));
    entity3->GetTransformComponent()->SetRotation(glm::vec3(0, 0, 0));
    ColliderComponent* boxCollider = new ColliderComponent(1.5, 3.5);
    entity3->AddComponent(boxCollider);
    //boxCollider->rigidBody->setType(reactphysics3d::BodyType::KINEMATIC);
    reactphysics3d::Transform capsulTransform = reactphysics3d::Transform();
    capsulTransform.setPosition(reactphysics3d::Vector3(0, 3, 0));

    boxCollider->collider->setLocalToBodyTransform(capsulTransform);
    boxCollider->rigidBody->setIsDebugEnabled(true);
    boxCollider->rigidBody->setMass(1);
    boxCollider->rigidBody->setAngularLockAxisFactor(reactphysics3d::Vector3(0, 1, 0));
    boxCollider->collider->getMaterial().setBounciness(0);
    boxCollider->collider->getMaterial().setFrictionCoefficient(1);
    

    CameraComponent* cameraComponent = new CameraComponent(CameraType::Perspective, renderer->width, renderer->height);

    MovementComponent* mov = new MovementComponent(boxCollider->rigidBody);

    entity3->AddComponent(mov);

    entity3->AddComponent(cameraComponent);

    TestInputComponent* input = new TestInputComponent();

    input->SetWindow(renderer->window);

    input->LockCursorToWindow();

    entity3->AddComponent(input);
    

    renderer->SetBackFaceCulling(true);
    renderer->SetDepthTest(true);



    entity->GetTransformComponent()->SetPosition(glm::vec3(0,0,1));

    renderer->shader = new Shader("Main_Vertex_Shader.glsl", "Main_Fragment_Shader.glsl");

    std::vector<std::string> skyCubeMap = {
    "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"
    };
    renderer->skybox = new Skybox(skyCubeMap, "SkySphere_Vertex.glsl", "SkySphere_Fragment.glsl");

    Light light(glm::vec3(1.0f, 1.0f, 1.0f), 5.0f, glm::vec3(-3.0f, -3.0f, 0.0f));

    renderer->AddLight(light);

    world->physicsHandler->EnableDebuging();



    while (!glfwWindowShouldClose(renderer->window) && shouldRun) 
    {
        timer.Update();
        float deltaTime = timer.GetDeltaTime();
        float currentTime = timer.GetCurrentTime();

        renderer->camera->UpdateWithEntity();

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
