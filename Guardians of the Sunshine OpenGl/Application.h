#pragma once
#include "World.h"
class Application
{
private:

	World* world;
	RenderManager* renderer;
	bool shouldRun;
	void Serlize(const std::string& name);


public:

	Application(const std::string& path);
	~Application();

	void Run();

	void Quit();

};

