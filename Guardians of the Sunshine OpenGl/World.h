#pragma once
#include "Entity.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RenderManager.h"

class World {
private:
    std::vector<Entity*> entities;  

public:
    World() = default;
    ~World();
    const std::vector<Entity*>& GetEntities() const { return entities; }

    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);


    glm::mat4 GetWorldMatrix(Entity* entity) const;
    void Serialize(nlohmann::json& jsonData) const;
    void Deserialize(const std::string& filepath);

    void Update(float deltaTime);
    void SERIALIZE(const std::string& name);


    void Render(RenderManager* Renderer);

    std::vector<Entity*> GetAllEntities();
};
