#include "Component.h"


Component::Component()
{

}

Component::~Component()
{

}

void Component::Update(float deltaTime)
{
  
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
