#pragma once
#include <vector>
#include <string>
#include <json/json.h>
#include <glm/glm.hpp>
#include "AssetManager.h"


class SceneDeserializer {
public:
    struct Transform {
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    };

    struct Renderer {
        std::string mesh;
        std::string shaderVertex;
        std::string shaderFragment;
        std::string texture;
    };

    struct Entity {
        std::string name;
        Transform transform;
        Renderer renderer;
    };

    struct RenderingSettings {
        bool backfaceCulling;
        bool depthTesting;
        bool blending;
    };

    static std::vector<Entity> DeserializeEntities(const nlohmann::json& sceneJson);
    static RenderingSettings DeserializeRenderingSettings(const nlohmann::json& sceneJson);
};