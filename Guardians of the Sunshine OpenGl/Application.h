#pragma once
#include "World.h"
#include "RenderManager.h"
#include "Timer.h"
#include "PhysicsManager.h"

class Application {
private:
    World* world = nullptr;
    RenderManager* renderer = nullptr;

    bool shouldRun = true;

    Timer timer;

    void SerializeApp(const std::string& name);

    std::string worldPath;

public:
    Application(const std::string& worldPath);
    ~Application();

    void Run();
    void Quit();
};
