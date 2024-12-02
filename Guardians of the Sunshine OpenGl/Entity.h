#pragma once
#include <string>
#include <vector>
#include "TransformComponent.h"

class Component;

class Entity
{

protected:
    std::string name ="Entity";
    std::vector<Component*> components; 
    std::vector<Entity*> children;  
    Entity* parent = nullptr;  
    bool isEnabled = true;
    TransformComponent* transform;


public:
    Entity(const std::string& entityName);
    ~Entity();

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);
    Component* GetComponent(const std::string& componentName) const;

    void SetParent(Entity* newParent);
    Entity* GetParent() const;
    void AddChild(Entity* child);
    void RemoveChild(Entity* child);
    const std::vector<Entity*>& GetChildren() const;

    void SetEnabled(bool enabled);
    bool IsEnabled() const;

    // Update all components
    void Update(float deltaTime);

    TransformComponent* GetTransformComponent();

    


};

