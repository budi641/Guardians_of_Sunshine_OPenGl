
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>

#include "Entity.h"

using namespace std;


    void Entity::UpdateTransform() {

        glm::mat4 LocalTransform = glm::mat4(1.0f);

        LocalTransform = glm::translate(LocalTransform, LocalPosition);
        LocalTransform = glm::rotate(LocalTransform, glm::radians(LocalRotation.x), glm::vec3(1, 0, 0));
        LocalTransform = glm::rotate(LocalTransform, glm::radians(LocalRotation.y), glm::vec3(0, 1, 0));
        LocalTransform = glm::rotate(LocalTransform, glm::radians(LocalRotation.z), glm::vec3(0, 0, 1));
        LocalTransform = glm::scale(LocalTransform, LocalScale);


        if (Parent) {

            WorldTransform = Parent->GetWorldTransform() * LocalTransform;
        }
        else {
            WorldTransform = LocalTransform;
        }


        for (int i = 0; i < Children.size(); i++) {
            Children[i].UpdateTransform();
        }
    }





    int Entity::getID()
    {
        return ID;
    }

    std::string Entity::getName()
    {
        return Name;
    }



    glm::mat4& Entity::getWorldTransform() {

        return WorldTransform;
    }

    Entity Entity::getParent()
    {
        return Parent;
    }

    std::vector<Entity>& Entity::getChildren()
    {
        return Children;
    }


    void Entity::setLocalPosition(const glm::vec3& position) {
        LocalPosition = position;
        UpdateTransform();
    }

    void Entity::setLocalRotation(const glm::vec3& rotation) {
        LocalRotation = rotation;
        UpdateTransform();
    }

    void Entity::setLocalScale(const glm::vec3& scale) {
        LocalScale = scale;
        UpdateTransform();
    }

    void Entity::setParent(Entity Parent = WorldEntity, Entity CurrentEntity)
    {
        if (Parent) {
            Parent.RemoveChild(Name);
        }

        this->Parent = Parent;

        if (Parent) {
            Parent.AddChild(CurrentEntity);
        }

        UpdateTransform();
    }
    void Entity::setName(string Name)
    {
        this->Name = Name;
    }
    void Entity::AddChild(Entity Child)
    {
        if (Child) {

            Children.push_back(Child);
        }

    }

    void Entity::RemoveChild(Entity Child)
    {
        for (int i = 0; i < Children.size(); i++)
        {
            if (Children[i].getName() == Child.getName())
            {
                Children.erase(Child);
                break;
            }
        }
    }

    void Entity::AddComponent(Component component)
    {
        if (component) {
            Components.push_back(component);
        }
    }




