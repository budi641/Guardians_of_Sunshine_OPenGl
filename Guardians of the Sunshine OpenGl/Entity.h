
#include "World.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
using namespace std;

class Entity :

    public World
{
private:
    std::string Name;

    glm::vec3 LocalPosition;
    glm::vec3 LocalRotation;
    glm::vec3 LocalScale;

    int ID;

    Entity Parent = WorldEntity;

    //PriorityQueue Children;
    vector <Entity> Children;
    vector <Component> Components;

    glm::mat4 WorldTransform;

    void UpdateTransform();




public:
    int getID();

    string getName();



    glm::mat4& getWorldTransform();


    Entity getParent();


    std::vector<Entity>& getChildren();



    Entity(string Name = "EntityName", glm::vec3 LocalPosition = { 0.0f,0.0f,0.0f }, glm::vec3 LocalRotation = { 0.0f,0.0f,0.0f }, glm::vec3 LocalScale = { 1.0f,1.0f,1.0f })
    {
        this->Name = Name;
        this->LocalPosition = LocalPosition;
        this->LocalRotation = LocalRotation;
        this->LocalScale = LocalScale;

        //serialize el id
        ID = random();
    }
    


    void setLocalPosition(const glm::vec3& position);


    void setLocalRotation(const glm::vec3& rotation);


    void setLocalScale(const glm::vec3& scale);



    void setParent(Entity Parent = WorldEntity, Entity CurrentEntity);


    void setName(string Name);


    void AddChild(Entity Child);



    void RemoveChild(Entity Child);



    void AddComponent(Component component);

};


