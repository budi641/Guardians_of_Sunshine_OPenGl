#include "World.h"
#include "Entity.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
World::~World() {
    for (auto entity : entities) {
        delete entity;
    }
}

void World::AddEntity(Entity* entity) {
    if (entity) {
        entities.push_back(entity);  
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
        entities.erase(it);  // Remove entity from the vector
        delete entity;       // Clean up the memory
    }
}

glm::mat4 World::GetWorldMatrix(Entity* entity) const {
    glm::mat4 worldMatrix = entity->GetTransformComponent()->GetTransformMatrix();

    if (entity->GetParent() != nullptr) {
        // If the entity has a parent, we multiply its world matrix by the parent's world matrix
        worldMatrix = GetWorldMatrix(entity->GetParent()) * worldMatrix;
    }

    return worldMatrix;
}

void World::Update(float deltaTime) {
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
        outFile << worldJson.dump(4);  // Write with pretty formatting
        outFile.close();
        std::cout << "World serialized successfully to " + name + ".json" << std::endl;
    }
    else {
        std::cout << "Error opening file for writing!" << std::endl;
    }
}
void World::Render() {
    for (auto entity : entities) {
        glm::mat4 worldMatrix = GetWorldMatrix(entity);


    }
}

std::vector<Entity*> World::GetAllEntities()
{
    return entities;
}
