#pragma once
#include <string>
#include<json/json.h>
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
    virtual void Serialize(nlohmann::json& jsonData) const = 0;
    virtual void Deserialize(const nlohmann::json& jsonData) = 0;
    Entity* GetParentEntity() const; 

    std::string GetComponentName();

    void SetComponentName(std::string name);

    void SetIsEnabled(bool enabled);

    bool GetIsEnabled() const;

    void SetParentEntity(Entity* parent);


};

