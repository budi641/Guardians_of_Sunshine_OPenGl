#include "World.h"
#include "Entity.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include "PhysicsManager.h"


World::World()
{
    physicsHandler = new PhysicsManager();
}

World::~World() {
    for (auto entity : entities) {
        delete entity;
    }
}

void World::AddEntity(Entity* entity) {
    if (entity) {
        entities.push_back(entity);  

        entity->world = this;

        for (auto child : entity->GetChildren())
        {
            AddEntity(child);
        }
    }
}
void World::Serialize(nlohmann::json& jsonData) const {
    jsonData["entities"] = nlohmann::json::array();  

    for (const Entity* entity : entities) {
        nlohmann::json entityData;
        entity->Serialize(entityData); 
        jsonData["entities"].push_back(entityData);
    }
}void World::Deserialize(const std::string& filePath) {
    // Open the file and check for errors
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << "\n";
        return;
    }

    // Parse the JSON data from the file
    nlohmann::json jsonData;
    try {
        file >> jsonData; // Read JSON from file
    }
    catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << "\n";
        return;
    }

    // Check if the "entities" key exists and is an array
    if (!jsonData.contains("entities") || !jsonData["entities"].is_array()) {
        std::cerr << "Invalid JSON format: Missing or invalid 'entities' key.\n";
        return;
    }

    // Deserialize each entity
    for (const auto& entityJson : jsonData["entities"]) {
        // Create the entity and pass JSON data for deserialization
        Entity* entity = new Entity(entityJson.value("name", "Unnamed Entity")); // Ensure name is passed
        entity->Deserialize(entityJson); // Deserialize the entity and its components/children
        AddEntity(entity); // Add the deserialized entity to the world
    }
}


void World::RemoveEntity(Entity* entity) {
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        entities.erase(it);  
        delete entity;       
    }
}

Entity* World::GetEntityByName(const std::string& name) {
    auto it = std::find_if(entities.begin(), entities.end(), [&name](Entity* entity) {
        return entity && entity->GetName() == name;
        });
    return (it != entities.end()) ? *it : nullptr;
}

glm::mat4 World::GetWorldMatrix(Entity* entity){
    glm::mat4 worldMatrix = entity->GetTransformComponent()->GetTransformMatrix();

    if (entity->GetParent() != nullptr) {
        worldMatrix = GetWorldMatrix(entity->GetParent()) * worldMatrix;
    }

    return worldMatrix;
}

glm::vec3 World::GetWorldPosition(Entity* entity)
{

    return glm::vec3(GetWorldMatrix(entity)[3][0], GetWorldMatrix(entity)[3][1], GetWorldMatrix(entity)[3][2]);
}


glm::quat World::GetWorldRotationQuat(Entity* entity) {
    glm::mat4 worldMatrix = GetWorldMatrix(entity);
    glm::mat3 rotationMatrix(worldMatrix);

    glm::quat worldRotation = glm::quat_cast(rotationMatrix);

    return worldRotation;
}

void World::Update(float deltaTime) {
    const float timeStep = 1.0f / 60.0f;

    physicsHandler->Update(timeStep);



    for (auto entity : entities) {
        entity->Update(deltaTime);
    }
}
void World::SERIALIZE(const std::string& name)
{
    nlohmann::json worldJson;
    this->Serialize(worldJson);
    std::ofstream outFile(name);
    if (outFile.is_open()) {
        outFile << worldJson.dump(4);  
        outFile.close();
        std::cout << "World serialized successfully to " + name + ".json" << std::endl;
    }
    else {
        std::cout << "Error opening file for writing!" << std::endl;
    }
}
void World::RenderWorld(RenderManager* Renderer) 
{
    SortEntitiesByDistance(Renderer);

    for (auto entity : entities) 
    {
        entity->RenderEntity(Renderer);
    }
}

void World::SortEntitiesByDistance(RenderManager* renderer)
{
    this->renderer = renderer;
    glm::vec3 cameraPos = renderer->camera->GetPosition();
    
    std::sort(entities.begin(), entities.end(), [this, &cameraPos](Entity* a, Entity* b) {
        glm::vec3 posA = this->GetWorldPosition(a);  
        glm::vec3 posB = this->GetWorldPosition(b);  
        float distA = glm::dot(posA - cameraPos, posA - cameraPos);  
        float distB = glm::dot(posB - cameraPos, posB - cameraPos);  
        return distA > distB;  
        });

}


