#pragma once
#include "World.h"
#include "Entity.cpp"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <iostream>
using namespace std;

class World
{
private:

    vector<Entity>Entities;

public:


    World()
    {
        cout << "World Created";
    }


    Entity CreateEntity(const std::string& name = "EntityName");


    void DestroyEntity(int ID);



    Entity FindEntity(int ID);


    void Update(Entity entity, string Name = "EntityName", glm::vec3 LocalPosition = { 0.0f,0.0f,0.0f }, glm::vec3 LocalRotation = { 0.0f,0.0f,0.0f }, glm::vec3 LocalScale = { 1.0f,1.0f,1.0f });

};

