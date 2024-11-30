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

    


    


    Entity World::CreateEntity(const std::string& name = "EntityName") {
        
        Entity entity(name);
        
        Entities.push_back(entity);

        return entity;


       
       
    }

    void World::DestroyEntity(int ID) {

        for (int i = 0; i < Entities.size(); i++)
        {

            if (ID == Entities[i].getID())
            {
                Entities.erase(Entities[i]);
                break;
            }
        }
    }

    Entity World::FindEntity(int ID) {

        for (int i = 0; i < Entities.size(); i++)
        {
            if (ID == Entities[i].getID())
            {
                return Entities[i];
             
            }
        }
    }


    void World::Update(Entity entity, string Name = "EntityName", glm::vec3 LocalPosition = { 0.0f,0.0f,0.0f }, glm::vec3 LocalRotation = { 0.0f,0.0f,0.0f }, glm::vec3 LocalScale = { 1.0f,1.0f,1.0f }) {
        
        entity.setName(Name);

        entity.setLocalPosition(LocalPosition);
        entity.setLocalRotation(LocalRotation);
        entity.setLocalScale(LocalScale);

    }

   

