#include "World.h"
#include "Entity.h"
#include <algorithm>

World::~World() 
{
    // Clean up all entities
    for (auto entity : entities)
    {
        delete entity;
    }
}

void World::AddEntity(Entity* entity) 
{
    if (entity) 
    {
        entities.push_back(entity);
    }
}

void World::RemoveEntity(Entity* entity) 
{
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end())
    {
        entities.erase(it);
        delete entity;  // Clean up the memory
    }
}

glm::mat4 World::GetWorldMatrix(Entity* entity) const
{
    glm::mat4 worldMatrix = entity->GetTransformComponent()->GetTransformMatrix();

    if (entity->GetParent() != nullptr) {
        // If the entity has a parent, multiply the parent's world matrix
        worldMatrix = GetWorldMatrix(entity->GetParent()) * worldMatrix;
    }

    return worldMatrix;
}

void World::Update(float deltaTime) {
    // Update logic (e.g., physics, input, etc.) can be added here for each entity
    for (auto entity : entities) {
        // Update logic for each entity
    }
}

void World::Render() {
    // Render all entities, taking their world matrices into account
    for (auto entity : entities) {
        glm::mat4 worldMatrix = GetWorldMatrix(entity);

        // Render logic here (send worldMatrix to shader)
    }
}
