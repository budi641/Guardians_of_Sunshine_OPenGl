#include "Application.h"
#include "StaticMeshComponent.h"
#include "SkeletalMeshComponent.h"
#include <iostream>
#include "ColliderComponent.h"
#include "TestInputComponent.h"
#include "CameraComponent.h"
#include "MovementComponent.h"
#include "Collision.h"



Application::Application(const std::string& path) : worldPath(path) 
{
    world = new World;
    renderer = new RenderManager(1600, 900, "Test App");
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


    renderer->SetBackFaceCulling(true);
    renderer->SetDepthTest(true);


    renderer->postProcessShader = new Shader("PPVert.glsl", "PPFrag.glsl");

    renderer->shader = new Shader("Main_Vertex_Shader.glsl", "Main_Fragment_Shader.glsl");

    std::vector<std::string> skyCubeMap = {
    "grid.png", "grid.png", "grid.png", "grid.png","grid.png", "grid.png" };
    renderer->skybox = new Skybox(skyCubeMap, "SkySphere_Vertex.glsl", "SkySphere_Fragment.glsl");


    Light directionalLight(
        glm::vec3(0.8f, 1.0f, 0.9f),
        0.7f,
        glm::vec3(1.0f, -1.0f, 0.0f)
    );

    Light pointLight(
        glm::vec3(1.0f, 0.0f, 0.0f),
        1.0f,
        glm::vec3(0.0f, 5.0f, 0.0f),
        10.0f
    );

    Light spotlight(
        glm::vec3(0.0f, 1.0f, 0.0f),
        1.0f,
        glm::vec3(0.0f, 5.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::radians(12.5f),
        glm::radians(17.5f)
    );


    renderer->AddLight(directionalLight);
    //renderer->AddLight(pointLight);
    //renderer->AddLight(spotlight);



    
        
    Material* terrainaterial = new Material(1,1,
        "Textures/TerrainTexture/terrain_Material_AlbedoTransparency.png",
        "Textures/TerrainTexture/terrain_Material_AO.png",
        "Textures/TerrainTexture/terrain_Material_Normal.png");
    auto* meshFloor = new StaticMeshComponent("land/terrain2.obj", terrainaterial);
    Entity* landMesh = new Entity("landMesh");
    landMesh->GetTransformComponent()->SetPosition(glm::vec3(20, 57.25, 0));
    landMesh->GetTransformComponent()->SetScale(glm::vec3(15));
    landMesh->GetTransformComponent()->SetRotation(glm::vec3(0, 180, 0));
    landMesh->AddComponent(meshFloor);
    Entity* land = new Entity("land");
    land->AddChild(landMesh);
    land->GetTransformComponent()->SetPosition(glm::vec3(0, -3, 0));
    world->AddEntity(land);
    ColliderComponent* landCollider = new ColliderComponent(700, 1, 700);
    land->AddComponent(landCollider);
    landCollider->rigidBody->setType(reactphysics3d::BodyType::STATIC);
    landCollider->collider->setCollisionCategoryBits(CATEGORY_GROUND);
    landCollider->collider->setCollideWithMaskBits(CATEGORY_PLAYER | CATEGORY_ENEMY);
 


    CameraComponent* cameraComponent = new CameraComponent(CameraType::Perspective, renderer->width, renderer->height);
    TestInputComponent* input = new TestInputComponent();
    input->SetWindow(renderer->window);
    input->LockCursorToWindow();


    Material* Finmat = new Material(2, 1,
        "finn/textures/finColor.png",
        "finn/textures/finSpecular.png",
        "finn/textures/finNormal.png");
    SkeletalMeshComponent* finnMeshComp = new SkeletalMeshComponent("finn/fin.dae", Finmat);
    Entity* finnMesh = new Entity("Mesh");
    finnMesh->AddComponent(finnMeshComp);
    finnMesh->GetTransformComponent()->SetRotation(glm::vec3(0,-90,0));
    finnMesh->GetTransformComponent()->SetPosition(glm::vec3(0, -1, -4));
    finnMesh->GetTransformComponent()->SetScale(glm::vec3(1));
    Entity* Finn = new Entity("Finn");
    Finn->AddChild(finnMesh);
    world->AddEntity(Finn);
    ColliderComponent* FinnCollider = new ColliderComponent(2, 4.5);
    Finn->AddComponent(FinnCollider);
    MovementComponent* movement = new MovementComponent(FinnCollider->rigidBody);
    Finn->AddComponent(movement);
    FinnCollider->rigidBody->setAngularLockAxisFactor(reactphysics3d::Vector3(0, 1, 0));
    FinnCollider->rigidBody->setMass(1);
    FinnCollider->collider->setCollisionCategoryBits(CATEGORY_PLAYER);
    FinnCollider->collider->setCollideWithMaskBits(CATEGORY_GROUND | CATEGORY_ENEMY | CATEGORY_COINS);



    Material* JakeMat = new Material(2, 1,
        "Textures/JakeTextures/jake_Material_AlbedoTransparency.png",
        "Textures/JakeTextures/jake_Material_AO.png",
        "Textures/JakeTextures/jake_Material_Normal.png");
    SkeletalMeshComponent* JakeMeshComp = new SkeletalMeshComponent("Models/jake/Jake_idle.dae", JakeMat);
    Entity* JakeMesh = new Entity("Mesh");
    JakeMesh->AddComponent(JakeMeshComp);
    JakeMesh->GetTransformComponent()->SetRotation(glm::vec3(0, 0, 0));
    JakeMesh->GetTransformComponent()->SetPosition(glm::vec3(0, -2.5, 0));
    JakeMesh->GetTransformComponent()->SetScale(glm::vec3(100));
    Entity* Jake = new Entity("Jake");
    Jake->GetTransformComponent()->SetPosition(glm::vec3(4, 0, 0));
    JakeMeshComp->idle = new Animation("Models/jake/Jake_idle.dae",JakeMeshComp->GetModel());
    JakeMeshComp->Run = new Animation("Models/jake/Jake_run.dae", JakeMeshComp->GetModel());
    JakeMeshComp->emote1 = new Animation("Models/jake/Jake_emote.dae", JakeMeshComp->GetModel());
    JakeMeshComp->emote2 = new Animation("Models/jake/Jake_emote2.dae", JakeMeshComp->GetModel());
    JakeMeshComp->attack = new Animation("Models/jake/Jake_attack.dae", JakeMeshComp->GetModel());
    Jake->AddChild(JakeMesh);
    world->AddEntity(Jake);
    ColliderComponent* JakeCollider = new ColliderComponent(2, 1.8);
    Jake->AddComponent(JakeCollider);
    MovementComponent* jakemovement = new MovementComponent(JakeCollider->rigidBody);
    Jake->AddComponent(jakemovement);
    JakeCollider->rigidBody->setAngularLockAxisFactor(reactphysics3d::Vector3(0, 1, 0));
    JakeCollider->rigidBody->setMass(1);
    JakeCollider->collider->setCollisionCategoryBits(CATEGORY_PLAYER);
    JakeCollider->collider->setCollideWithMaskBits(CATEGORY_GROUND | CATEGORY_ENEMY | CATEGORY_COINS);




    
    Material* BeeMat = new Material(2, 1,
        "Textures/BeMonsterTexture/BeeMonster_Material_AlbedoTransparency.png",
        "Textures/BeMonsterTexture/BeeMonster_Material_AO.png",
        "Textures/BeMonsterTexture/BeeMonster_Material_Normal.png");
    StaticMeshComponent* BeeMeshComp = new StaticMeshComponent("Models/Bee/BeeMonster.obj", BeeMat);
    Entity* BeeMesh = new Entity("Mesh");
    BeeMesh->AddComponent(BeeMeshComp);
    BeeMesh->GetTransformComponent()->SetRotation(glm::vec3(0, 0, 0));
    BeeMesh->GetTransformComponent()->SetPosition(glm::vec3(0, 2.5, 0));
    BeeMesh->GetTransformComponent()->SetScale(glm::vec3(5));
    Entity* Bee = new Entity("Bee");
    Bee->GetTransformComponent()->SetPosition(glm::vec3(-8, 0, 75));
    Bee->AddChild(BeeMesh);
    world->AddEntity(Bee);
    ColliderComponent* BeeCollider = new ColliderComponent(7, 9);
    Bee->AddComponent(BeeCollider);
    MovementComponent* Beemovement = new MovementComponent(BeeCollider->rigidBody);
    Bee->AddComponent(Beemovement);
    Beemovement->moveRandom = true;
    Beemovement->speed = 50;
    Beemovement->maxSpeed = 60;
    BeeCollider->rigidBody->setAngularLockAxisFactor(reactphysics3d::Vector3(1, 1, 1));
    BeeCollider->rigidBody->setMass(1);
    BeeCollider->collider->setCollisionCategoryBits(CATEGORY_ENEMY);
    BeeCollider->collider->setCollideWithMaskBits(CATEGORY_GROUND | CATEGORY_PLAYER);

    Material* RabitMat = new Material(2, 1,
        "Textures/rabbitMonsterTexture/rabitmonster_Material_AlbedoTransparency.png",
        "Textures/rabbitMonsterTexture/rabitmonster_Material_AO.png",
        "Textures/rabbitMonsterTexture/rabitmonster_Material_Normal.png");
    StaticMeshComponent* RabitMeshComp = new StaticMeshComponent("Models/Rabbit/rabitmonster.obj", RabitMat);
    Entity* RabitMesh = new Entity("Mesh");
    RabitMesh->AddComponent(RabitMeshComp);
    RabitMesh->GetTransformComponent()->SetRotation(glm::vec3(0, 0, 0));
    RabitMesh->GetTransformComponent()->SetPosition(glm::vec3(0, -5, 5));
    RabitMesh->GetTransformComponent()->SetScale(glm::vec3(3.5));
    Entity* Rabit = new Entity("Rabit");
    Rabit->GetTransformComponent()->SetPosition(glm::vec3(-30, 0, 50));
    Rabit->AddChild(RabitMesh);
    world->AddEntity(Rabit);
    ColliderComponent* RabitCollider = new ColliderComponent(5.5, 7);
    Rabit->AddComponent(RabitCollider);
    MovementComponent* Rabitmovement = new MovementComponent(RabitCollider->rigidBody);
    Rabit->AddComponent(Rabitmovement);
    Rabitmovement->moveRandom = true;
    Rabitmovement->speed = 50;
    Rabitmovement->maxSpeed = 60;
    RabitCollider->rigidBody->setAngularLockAxisFactor(reactphysics3d::Vector3(0, 1, 0));
    RabitCollider->rigidBody->setMass(1);
    RabitCollider->collider->setCollisionCategoryBits(CATEGORY_ENEMY);
    FinnCollider->collider->setCollideWithMaskBits(CATEGORY_GROUND | CATEGORY_PLAYER);

    for (int i = 0; i < 5; i++)
    {
        Material* CoinMat = new Material(50, 1,
            "Textures/CoinTexture/coin_Material_AlbedoTransparency.png",
            "Textures/CoinTexture/coin_Material_AO.png",
            "Textures/CoinTexture/coin_Material_Normal.png");
        StaticMeshComponent* coinMeshComp = new StaticMeshComponent("Models/coin/coin.obj", CoinMat);
        Entity* coinMesh = new Entity("CoinMesh");
        coinMesh->AddComponent(coinMeshComp);
        coinMesh->GetTransformComponent()->SetRotation(glm::vec3(0, 0, 0));
        coinMesh->GetTransformComponent()->SetPosition(glm::vec3(0, 0, 0));
        coinMesh->GetTransformComponent()->SetScale(glm::vec3(1));
        Entity* coin = new Entity("Coin");
        coin->GetTransformComponent()->SetPosition(glm::vec3(5*i, 0, 25 + 4*i));
        coin->AddChild(coinMesh);
        world->AddEntity(coin);
        ColliderComponent* coinCollider = new ColliderComponent(2);
        coin->AddComponent(coinCollider);
        coinCollider->rigidBody->setAngularLockAxisFactor(reactphysics3d::Vector3(0, 1, 0));
        coinCollider->rigidBody->setMass(1);
        coinCollider->collider->setCollisionCategoryBits(CATEGORY_COINS);
        coinCollider->collider->setCollideWithMaskBits(CATEGORY_PLAYER);
     }




    
    Jake->AddComponent(cameraComponent);
    Jake->AddComponent(input);

   


    



    //world->physicsHandler->EnableDebuging();

    

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
