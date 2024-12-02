#include "Entity.h"
#include "Component.h"
#include <algorithm>
#include "TransformComponent.h"

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

void Entity::AddComponent(Component* component)
{
    if (component != nullptr)
    {
        components.push_back(component);
        component->SetIsEnabled(isEnabled);
        component->SetParentEntity(this);
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
    // Remove this entity from its current parent's children list
    if (parent != nullptr)
    {
        parent->RemoveChild(this);
    }

    parent = newParent;

    // Add this entity to the new parent's children list
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

    // Propagate the state change to each component
    for (auto component : components)
    {
        component->SetIsEnabled(enabled);
    }

    // Update all children if any
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

    // Update all components
    for (auto component : components)
    {
        if (component->GetIsEnabled())
        {
            component->Update(deltaTime);  // Update only enabled components
        }
    }

    // Update all children if any
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
