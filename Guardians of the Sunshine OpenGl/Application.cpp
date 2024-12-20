#include "Application.h"
#include "MeshRenderer.h"
#include <iostream>

Application::Application(const std::string& path) : worldPath(path) 
{
    world = new World;
#include <json/json.h>
using json = nlohmann::json;

#include <fstream>

using json = nlohmann::json;

void Application::SerializeApp(const std::string& filename) {
    json appJson;

    if (world) {
        json worldJson;
        world->Serialize(worldJson);
        appJson["World"] = worldJson;
    }
    else {
        appJson["World"] = json::object(); 
    }

    if (renderer) {
        json rendererJson;
        renderer->Serialize(rendererJson);
        appJson["RenderManager"] = rendererJson;
    }
    else {
        appJson["RenderManager"] = json::object(); 
    }

    appJson["ShouldRun"] = shouldRun;
    appJson["WorldPath"] = worldPath;

    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << appJson.dump(4); 
        outFile.close();
        std::cout << "Serialized Application data to file: " << filename << std::endl;
    }
    else {
        std::cerr << "Failed to write to file: " << filename << std::endl;
    }
}
Application::Application(const std::string& path, const char* windowTitle) : worldPath(path)
{
    world = new World;
    std::ifstream inFile(path);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open the file: " << path << std::endl;
        return;
    }
    json appJson;
    inFile >> appJson;
    int width = appJson["RenderManager"]["width"].get<int>();
    int height = appJson["RenderManager"]["height"].get<int>();
    renderer = new RenderManager(width, height, windowTitle);
    renderer->Deserialize(appJson);
    world->Deserialize(path);

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
    world->AddEntity(entity);
    entity->GetTransformComponent()->SetPosition(glm::vec3(0, 0, 2));



    auto* entity3 = new Entity("Player3");

    auto* meshComp3 = new MeshRenderer("path to model", "container2.png", "container2_specular.png",
        glm::vec3(0.0f), glm::vec3(0.3f), glm::vec3(0.2f), 0.4f);

    entity3->AddComponent(meshComp3);
    world->AddEntity(entity3);
    entity3->GetTransformComponent()->SetPosition(glm::vec3(0, 0, -2));

    renderer->SetBackFaceCulling(true);
    auto* entity2 = new Entity("Player2");

    entity->AddChild(entity2);
    auto* meshComp = new MeshRenderer("path to model", "container2.png", "container2_specular.png",
        glm::vec3(0.0f), glm::vec3(0.3f), glm::vec3(0.2f), 0.4f);
    entity->AddComponent(meshComp);

    renderer->SetBackFaceCulling(false);

    renderer->SetDepthTest(true);



    entity->GetTransformComponent()->SetPosition(glm::vec3(0,0,1));
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

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL Error: " << error << std::endl;
        }


        renderer->Render();
        world->Render(renderer);

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
