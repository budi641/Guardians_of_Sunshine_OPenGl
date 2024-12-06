#include "Application.h"
#include "MeshRenderer.h"

void Application::Serlize(const std::string& name)
{
}

Application::Application(const std::string& path)
{
}

Application::~Application()
{
}

void Application::Run()
{
	renderer = new RenderManager(1270, 720, "Test App");

	if (!renderer->window)return;

	renderer->shader= new Shader("Vertex_Shader.glsl", "Fragment_Shader.glsl");

	world = new World;

	Entity me("name");

	world->AddEntity(&me);

	MeshRenderer meshComp("path to model", "container2.png", "container2_specular.png", glm::vec3(0.0f), glm::vec3(0.3f), glm::vec3(0.2f), 0.4f);

	me.AddComponent(&meshComp);

	renderer->camera = new Camera(CameraType::Perspective, renderer->width, renderer->height);


	renderer->camera->SetPosition(glm::vec3(0, 1, 5));

	renderer->light = new Light(glm::vec3(1.0f, 1.0f, 1.0f), 5.0f, glm::vec3(-3.0f, -3.0f, 0.0f));

	std::vector<std::string> skyCubeMap = {
		"right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"
	};

	renderer->skybox = new Skybox(skyCubeMap, "SkySphere_Vertex.glsl", "SkySphere_Fragment.glsl");

	shouldRun = true;

	while (!glfwWindowShouldClose(renderer->window) && shouldRun)
	{
		renderer->Render();

		world->Render(renderer);

	}


}


void Application::Quit()
{
	shouldRun = false;
	glfwTerminate();

}
