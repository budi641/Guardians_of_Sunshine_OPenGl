#include "Entity.h"
#include "Component.h"
#include <algorithm>
#include "TransformComponent.h"
#include "MeshRenderer.h"
#include "RenderManager.h"

Entity::Entity(const std::string& entityName)
{
    name = entityName;
    AddComponent(transform);
}

Entity::~Entity()
{
    for (auto component : components)
    {
        delete component;
    }

    for (auto child : children)
    {
        delete child;
    }
}

void Entity::Serialize(nlohmann::json& jsonData) const {
    jsonData["name"] = name;
    jsonData["enabled"] = isEnabled;

    // Serialize components
    jsonData["components"] = nlohmann::json::array();
    for (const Component* component : components) {
        nlohmann::json componentData;
        component->Serialize(componentData);
        jsonData["components"].push_back(componentData);
    }

    // Serialize children
    jsonData["children"] = nlohmann::json::array();
    for (const Entity* child : children) {
        nlohmann::json childData;
        child->Serialize(childData);
        jsonData["children"].push_back(childData);
    }
}

void Entity::AddComponent(Component* component)
{
    if (component != nullptr)
    {
        components.push_back(component);
        component->SetIsEnabled(isEnabled);
        component->SetParentEntity(this);
    }
}

void Entity::Deserialize(const nlohmann::json& jsonData) {
    name = jsonData.value("name", "Unnamed Entity");

    if (jsonData.contains("components")) {
        for (const auto& componentJson : jsonData["components"]) {
            std::string type = componentJson.value("type", "");

            if (type == "TransformComponent") {
                if (!transform) {
                    transform = new TransformComponent();
                    AddComponent(transform);
                }
                transform->Deserialize(componentJson);
            }
        }
    }

    if (jsonData.contains("children")) {
        for (const auto& childJson : jsonData["children"]) {
            Entity* child = new Entity(childJson.value("name", "Unnamed Entity"));
            child->Deserialize(childJson);
            AddChild(child);
        }
    }
}

void Entity::RemoveComponent(Component* component)
{
    auto it = std::find(components.begin(), components.end(), component);
    if (it != components.end())
    {
        components.erase(it);
    }
}

Component* Entity::GetComponent(const std::string& componentName) const
{
    for (auto component : components)
    {
        if (component->GetComponentName() == componentName)
        {
            return component;
        }
    }
    return nullptr;
}

void Entity::SetParent(Entity* newParent)
{
    if (parent != nullptr)
    {
        parent->RemoveChild(this);
    }

    parent = newParent;

    if (parent != nullptr)
    {
        parent->AddChild(this);
    }
}

Entity* Entity::GetParent() const
{
    return parent;
}

void Entity::AddChild(Entity* child)
{
    if (child != nullptr && std::find(children.begin(), children.end(), child) == children.end())
    {
        children.push_back(child);
        child->SetParent(this);
    }
}

void Entity::RemoveChild(Entity* child)
{
    auto it = std::find(children.begin(), children.end(), child);
    if (it != children.end())
    {
        children.erase(it);
    }
}

const std::vector<Entity*>& Entity::GetChildren() const
{
    return children;
}

void Entity::SetEnabled(bool enabled)
{
    isEnabled = enabled;

    for (auto component : components)
    {
        component->SetIsEnabled(enabled);
    }

    for (auto child : children)
    {
        child->SetEnabled(enabled);
    }
}

bool Entity::IsEnabled() const
{
    return isEnabled;
}

void Entity::Update(float deltaTime)
{
    if (!isEnabled) return;

    for (auto component : components)
    {
        if (component->GetIsEnabled())
        {
            component->Update(deltaTime);
        }
    }

    for (auto child : children)
    {
        child->Update(deltaTime);
    }
}

TransformComponent* Entity::GetTransformComponent()
{
    return transform;
}

std::string Entity::GetName()
{
    return name;
}

std::vector<Component*> Entity::GetMeshRenderComponents()
{
    std::vector<Component*> Meshcomponents;

    for (auto component : this->components)
    {
        if (dynamic_cast<MeshRenderer*>(component))
        {
            Meshcomponents.push_back(component);
        }
    }

    return Meshcomponents;
}

void Entity::RenderEntity(RenderManager* renderer)
{
    for (Component* component : components)
    {
        MeshRenderer* mesh = dynamic_cast<MeshRenderer*>(component);

        if (mesh)
        {
            mesh->Render(renderer, world->GetWorldMatrix(this));
        }
    }
}
