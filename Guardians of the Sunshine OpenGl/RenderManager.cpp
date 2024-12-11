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
    if (jsonData.contains("RenderManager") &&
        jsonData["RenderManager"].contains("Light") &&
        !jsonData["RenderManager"]["Light"].is_null()) {

        // Extract light data
        const auto& lightData = jsonData["RenderManager"]["Light"];

        // Parse color, intensity, and direction
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

        // Ensure no memory leaks and allocate new light
        delete light; // Clean up any previous light instance
        light = new Light(color, intensity, direction);
    }
    
    std::cout << light->getcolor().x;
    if (jsonData.contains("RenderManager") &&
        jsonData["RenderManager"].contains("Skybox") &&
        !jsonData["RenderManager"]["Skybox"].is_null()) {

        // Extract Skybox data
        const auto& skyboxData = jsonData["RenderManager"]["Skybox"];

        // Parse faces, vertexShaderPath, and fragmentShaderPath
        std::vector<std::string> faces = skyboxData["faces"].get<std::vector<std::string>>();
        std::string vertexShaderPath = skyboxData["vertexShaderPath"];
        std::string fragmentShaderPath = skyboxData["fragmentShaderPath"];

        // Ensure no memory leaks and allocate a new Skybox object
        delete skybox; // Clean up any previous skybox instance
        skybox = new Skybox(faces, vertexShaderPath, fragmentShaderPath);
    }
    // Deserialize Camera
    if (jsonData.contains("RenderManager") &&
        jsonData["RenderManager"].contains("Camera") &&
        !jsonData["RenderManager"]["Camera"].is_null()) {

        const auto& cameraData = jsonData["RenderManager"]["Camera"];

        // Parse camera properties
        CameraType type = cameraData["type"] == "Perspective" ? CameraType::Perspective : CameraType::Orthographic;
        float fov = cameraData["fov"];
        float nearPlane = cameraData["nearPlane"];
        float farPlane = cameraData["farPlane"];
        float orthoHeight = cameraData["orthoHeight"];

        // Delete existing camera and create a new one to avoid memory leaks
        delete camera;
        camera = new Camera(type, width, height, fov, nearPlane, farPlane, orthoHeight);
    }

    // Deserialize Shader
    if (jsonData.contains("RenderManager") &&
        jsonData["RenderManager"].contains("Shader") &&
        !jsonData["RenderManager"]["Shader"].is_null()) {

        const auto& shaderData = jsonData["RenderManager"]["Shader"];

        // Parse shader file paths
        std::string vertexSource = shaderData["vertexSource"];
        std::string fragmentSource = shaderData["fragmentSource"];

        // Delete existing shader and create a new one to avoid memory leaks
        delete shader;
        shader = new Shader(vertexSource, fragmentSource);
    }
}



int RenderManager::getheight()
{
    return height;
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
