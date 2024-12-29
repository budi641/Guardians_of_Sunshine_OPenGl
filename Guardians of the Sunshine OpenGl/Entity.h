#pragma once
#include <string>
#include <vector>
#include "TransformComponent.h"
#include <json/json.h>
#include <reactphysics3d/reactphysics3d.h>


class Component;

class World;

class MeshRendererComponent;

class RenderManager;

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

    template <typename T>
    T* GetComponentByClass() const {
        for (Component* component : components) {
            T* castedComponent = dynamic_cast<T*>(component);
            if (castedComponent != nullptr) {
                return castedComponent;
            }
        }
        return nullptr;
    }

    Entity* GetChildByName(const std::string& childName) const;

    void Update(float deltaTime);
    void Serialize(nlohmann::json& jsonData) const;
    void Deserialize(const nlohmann::json& jsonData);
    TransformComponent* GetTransformComponent();
    std::vector<Component*> GetMeshRenderComponents();

    void RenderEntity(RenderManager* renderer);

    World* world;

    reactphysics3d::Transform GetEntityPhysicsTransform();
    


};

