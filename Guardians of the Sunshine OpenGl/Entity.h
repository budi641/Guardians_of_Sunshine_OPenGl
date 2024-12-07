#pragma once
#include <string>
#include <vector>
#include "TransformComponent.h"
#include <json/json.h>

class Component;

class World;

class Entity
{

protected:
    std::string name ="Entity";
    std::vector<Component*> components; 
    std::vector<Entity*> children;  
    Entity* parent = nullptr;  
    bool isEnabled = true;
    TransformComponent* transform = new TransformComponent();;


public:
    Entity(const std::string& entityName);
    ~Entity();

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);
    Component* GetComponent(const std::string& componentName) const;


    std::string GetName();

    void SetParent(Entity* newParent);
    Entity* GetParent() const;
    void AddChild(Entity* child);
    void RemoveChild(Entity* child);
    const std::vector<Entity*>& GetChildren() const;

    void SetEnabled(bool enabled);
    bool IsEnabled() const;

    void Update(float deltaTime);
    void Serialize(nlohmann::json& jsonData) const;
    void Deserialize(const nlohmann::json& jsonData);
    TransformComponent* GetTransformComponent();
    std::vector<Component*> GetMeshRenderComponents();

    void Render()

    World* world;
    


};

