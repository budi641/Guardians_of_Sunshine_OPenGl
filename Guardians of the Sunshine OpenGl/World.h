#pragma once
#include "Entity.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RenderManager.h"


class PhysicsManager;


class World {
private:
    std::vector<Entity*> entities;  

    void SortEntitiesByDistance(RenderManager* renderer);

public:
    World();
    ~World();

    PhysicsManager* physicsHandler = nullptr;

    RenderManager* renderer = nullptr;
    
    const std::vector<Entity*>& GetEntities() const { return entities; }

    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);

    Entity* GetEntityByName(const std::string& name);

    glm::mat4 GetWorldMatrix(Entity* entity);
    glm::vec3 GetWorldPosition(Entity* entity);
    glm::quat GetWorldRotationQuat(Entity* entity);
    void Serialize(nlohmann::json& jsonData) const;
    void Deserialize(const std::string& filepath);

    void Update(float deltaTime);
    void SERIALIZE(const std::string& name);

    void RenderWorld(RenderManager* Renderer);


};
