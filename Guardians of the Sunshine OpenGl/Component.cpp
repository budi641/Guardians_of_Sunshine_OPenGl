#include "Component.h"


Component::Component()
{
    // Constructor logic (if needed)
}

Component::~Component()
{
    // Destructor logic (if needed)
}

void Component::Update(float deltaTime)
{
    // Update logic for derived components
}

Entity* Component::GetParentEntity() const
{
    return parent;
}

std::string Component::GetComponentName()
{
    return this->name;
}

void Component::SetComponentName(std::string name)
{
    this->name = name;
}

void Component::SetIsEnabled(bool enabled)
{
    this->isEnabled = enabled;
}

bool Component::GetIsEnabled() const
{
    return this->isEnabled;
}

void Component::SetParentEntity(Entity* parent)
{
    this->parent = parent;
}
