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
