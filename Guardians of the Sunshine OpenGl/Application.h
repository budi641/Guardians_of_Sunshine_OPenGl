#pragma once
#include "World.h"
#include "RenderManager.h"
#include "Timer.h"
#include "InputHandler.h"

#include <json/json.h>
class Application {
private:
    World* world = nullptr;
    RenderManager* renderer = nullptr;
    InputHandler inputHandler;
    bool shouldRun = true;

    Timer timer;

    void SerializeApp(const std::string& name);

    std::string worldPath;

public:
    Application(const std::string& worldPath, const char* windowTitle);
    ~Application();
    void SerializeApp(const std::string& filename);

    void Run();
    void Quit();
};
