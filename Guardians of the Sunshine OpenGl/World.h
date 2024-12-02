#pragma once
#include "Entity.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class World {
private:
    std::vector<Entity*> entities;  // All entities in the world

public:
    World() = default;
    ~World();

    // Add and remove entities from the world
    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);

    // Calculate the world transformation matrix of an entity recursively
    glm::mat4 GetWorldMatrix(Entity* entity) const;

    // Update all entities in the world (called once per frame)
    void Update(float deltaTime);

    // Render all entities in the world (called once per frame)
    void Render();
};
