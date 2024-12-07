#include "RenderManager.h"
#include <iostream>
#include<json/json.h>
using json = nlohmann::json;

RenderManager::RenderManager(int width, int height, const char* windowTitle)
    : width(width), height(height) {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        throw std::runtime_error("GLFW initialization failed");
    }

    // Set GLFW window hints (OpenGL version and profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the GLFW window
    window = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        throw std::runtime_error("GLFW window creation failed");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        throw std::runtime_error("GLAD initialization failed");
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height) {
        glViewport(0, 0, width, height);
        });

    SetUpOpenGL();
}

RenderManager::~RenderManager() {
    delete skybox;
    delete camera;
    delete shader;
    delete light;

    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

void RenderManager::SetUpOpenGL() {
    if (enableDepthTest) {
        glEnable(GL_DEPTH_TEST);

    }

    if (enableBackFaceCulling) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }

    glViewport(0, 0, width, height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Default background color
}

void RenderManager::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (skybox && camera) {
        skybox->Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
    }

    if (shader) {
        shader->Bind();
    }

    if (camera && shader) {
        camera->UpdateProjection(*shader);
    }


}

void RenderManager::Deserialize(const nlohmann::json& jsonData) {
    // Deserialize basic settings
    if (jsonData.contains("width")) {
        width = jsonData["width"];
    }
    if (jsonData.contains("height")) {
        height = jsonData["height"];
    }
    if (jsonData.contains("enableDepthTest")) {
        enableDepthTest = jsonData["enableDepthTest"];
        SetDepthTest(enableDepthTest);
    }
    if (jsonData.contains("enableBackFaceCulling")) {
        enableBackFaceCulling = jsonData["enableBackFaceCulling"];
        SetBackFaceCulling(enableBackFaceCulling);
    }

    // Deserialize Light
    if (jsonData.contains("Light") && !jsonData["Light"].is_null()) {
        const auto& lightData = jsonData["Light"];
        glm::vec3 color(
            lightData["color"][0],
            lightData["color"][1],
            lightData["color"][2]
        );
        float intensity = lightData["intensity"];
        glm::vec3 direction(
            lightData["direction"][0],
            lightData["direction"][1],
            lightData["direction"][2]
        );

        delete light; // Ensure no memory leaks
        light = new Light(color, intensity, direction);
    }

    // Deserialize Skybox
    if (jsonData.contains("Skybox") && !jsonData["Skybox"].is_null()) {
        const auto& skyboxData = jsonData["Skybox"];
        std::vector<std::string> faces = skyboxData["faces"].get<std::vector<std::string>>();
        std::string vertexShaderPath = skyboxData["vertexShaderPath"];
        std::string fragmentShaderPath = skyboxData["fragmentShaderPath"];

        delete skybox; // Ensure no memory leaks
        skybox = new Skybox(faces, vertexShaderPath, fragmentShaderPath);
    }

    // Deserialize Camera
    if (jsonData.contains("Camera") && !jsonData["Camera"].is_null()) {
        const auto& cameraData = jsonData["Camera"];
        CameraType type = cameraData["type"] == "Perspective" ? CameraType::Perspective : CameraType::Orthographic;
        float fov = cameraData["fov"];
        float nearPlane = cameraData["nearPlane"];
        float farPlane = cameraData["farPlane"];
        float orthoHeight = cameraData["orthoHeight"];

        delete camera; // Ensure no memory leaks
        camera = new Camera(type, width, height, fov, nearPlane, farPlane, orthoHeight);
    }

    // Deserialize Shader
    if (jsonData.contains("Shader") && !jsonData["Shader"].is_null()) {
        const auto& shaderData = jsonData["Shader"];
        std::string vertexSource = shaderData["vertexSource"];
        std::string fragmentSource = shaderData["fragmentSource"];

        delete shader; // Ensure no memory leaks
        shader = new Shader(vertexSource, fragmentSource);
    }
}



void RenderManager::SetDepthTest(bool enable) {
    if (enable) {
        glEnable(GL_DEPTH_TEST);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }
    enableDepthTest = enable;
}
void RenderManager::Serialize(nlohmann::json& jsonData)  {
    jsonData["width"] = width;
    jsonData["height"] = height;
    jsonData["enableDepthTest"] = enableDepthTest;
    jsonData["enableBackFaceCulling"] = enableBackFaceCulling;

    // Serialize Light, Skybox, Camera, Shader (check if they are not null before serializing)
    if (light) {
        nlohmann::json lightJson;
        light->Serialize(lightJson);  // Serialize Light properties
        jsonData["Light"] = lightJson;
    }
    else {
        jsonData["Light"] = json::object(); // Empty object if light is null
    }
    
    if (skybox) {
        nlohmann::json skyboxJson;
        skybox->Serialize(skyboxJson); // Assuming Skybox has a Serialize method
        jsonData["Skybox"] = skyboxJson;
    }
    else {
        jsonData["Skybox"] = json::object(); // Empty object if skybox is null
    }

    if (camera) {
        nlohmann::json cameraJson;
        camera->Serialize(cameraJson); // Assuming Camera has a Serialize method
        jsonData["Camera"] = cameraJson;
    }
    else {
        jsonData["Camera"] = json::object(); // Empty object if camera is null
    }
    
    if (shader) {
        nlohmann::json shaderJson;
        shader->Serialize(shaderJson); // Assuming Shader has a Serialize method
        jsonData["Shader"] = shaderJson;
    }
    else {
        jsonData["Shader"] = json::object(); // Empty object if shader is null
    }
}


void RenderManager::SetBackFaceCulling(bool enable) {
    if (enable) {
        glEnable(GL_CULL_FACE);
    }
    else {
        glDisable(GL_CULL_FACE);
    }
    enableBackFaceCulling = enable;
}
