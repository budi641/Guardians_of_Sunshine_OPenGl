#include "SceneDeserializer.h"
#include <fstream>
#include <iostream>
#include <json/json.h>

using json = nlohmann::json;

void SceneDeserializer::Deserialize(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open scene file: " << filePath << std::endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    const auto& shaders = jsonData["shaders"];
    std::string vertexShaderPath = shaders["vertex"];
    std::string fragmentShaderPath = shaders["fragment"];
    GLuint shaderProgram = AssetManager::LoadShader(vertexShaderPath, fragmentShaderPath);

    const auto& textures = jsonData["textures"];
    for (auto it = textures.begin(); it != textures.end(); ++it) {
        std::string textureName = it.key();
        std::string texturePath = it.value();
        AssetManager::LoadTexture(texturePath);
    }

    const auto& models = jsonData["models"];
    for (auto it = models.begin(); it != models.end(); ++it) {
        std::string modelName = it.key();
        std::string modelPath = it.value();
        AssetManager::LoadModel(modelPath);
    }

    const auto& entities = jsonData["entities"];
    for (const auto& entity : entities) {
        std::string name = entity["name"];
        const auto& components = entity["components"];

        const auto& transform = components["transform"];
        auto position = transform["position"].get<std::vector<float>>();
        auto rotation = transform["rotation"].get<std::vector<float>>();
        auto scale = transform["scale"].get<std::vector<float>>();

        const auto& renderer = components["renderer"];
        std::string mesh = renderer["mesh"];
        const auto& shader = renderer["shader"];
        std::string vertexShader = shader["vertex"];
        std::string fragmentShader = shader["fragment"];
        std::string texture = renderer["texture"];

        GLuint meshID = AssetManager::GetModel(mesh);
        GLuint shaderID = AssetManager::GetShader(vertexShader + fragmentShader);
        GLuint textureID = AssetManager::GetTexture(texture);



        const auto& rendering = jsonData["rendering"];
        bool backfaceCulling = rendering["backface_culling"];
        bool depthTesting = rendering["depth_testing"];
        bool blending = rendering["blending"];

        if (backfaceCulling) glEnable(GL_CULL_FACE);
        if (depthTesting) glEnable(GL_DEPTH_TEST);
        if (blending) glEnable(GL_BLEND);

    }