#include "World.h"
#include "Entity.h"
#include <algorithm>

World::~World() {
    // Clean up all entities in the world to avoid memory leaks
    for (auto entity : entities) {
        delete entity;
    }
}

void World::AddEntity(Entity* entity) {
    if (entity) {
        entities.push_back(entity);  // Add entity to the world
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
    // Iterate through all entities in the world and update them
    for (auto entity : entities) {
        // Here we could update components like Physics, AI, etc. For now, we just call Update on each entity
        entity->Update(deltaTime);
    }
}

void World::Render() {
    // Iterate through all entities and render them
    for (auto entity : entities) {
        glm::mat4 worldMatrix = GetWorldMatrix(entity);

        // Render logic here: For example, you would send worldMatrix to the shader for each entity
        // Example:
        // shader.SetMat4("model", worldMatrix);
        // entity->Render();
    }
}
