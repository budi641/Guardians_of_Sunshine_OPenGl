#pragma once
#include <string>

class Entity;

class Component
{

protected:
	Entity* parent =nullptr;

	std::string name = "component";

    bool isEnabled = true;

public:
    Component();
    virtual ~Component();
   
    virtual void Update(float deltaTime); 

    Entity* GetParentEntity() const; 

    std::string GetComponentName();

    void SetComponentName(std::string name);

    void SetIsEnabled(bool enabled);

    bool GetIsEnabled() const;

    void SetParentEntity(Entity* parent);


};

