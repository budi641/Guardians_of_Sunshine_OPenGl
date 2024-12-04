#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include "World.h"
#include "Entity.h"
#include<json/json.h>
#include"Component.h"
#include "TransformComponent.h"
#include <fstream>

void PrintMat4(const glm::mat4& mat) {
    const float* data = glm::value_ptr(mat);
    for (int i = 0; i < 4; ++i) {
        std::cout << "[ ";
        for (int j = 0; j < 4; ++j) {
            std::cout << data[i * 4 + j] << " ";
        }
        std::cout << "]" << std::endl;
    }
}

int main() {
    // Create a new world
    World world;

    // Create some entities with transform components and children
    Entity* entity1 = new Entity("Entity1");
    TransformComponent* transform1 = new TransformComponent();  // Add a transform component to entity1
    entity1->AddComponent(transform1);

    Entity* childEntity1 = new Entity("ChildEntity1");
    TransformComponent* transformChild1 = new TransformComponent();  // Add transform to child entity
    childEntity1->AddComponent(transformChild1);
    entity1->AddChild(childEntity1);  // Add a child to entity1

    Entity* entity2 = new Entity("Entity2");
    TransformComponent* transform2 = new TransformComponent();  // Add a transform component to entity2
    entity2->AddComponent(transform2);

    // Add entities to the world
    world.AddEntity(entity1);
    world.AddEntity(entity2);

    // Serialize the world to JSON
    nlohmann::json worldJson;
    world.Serialize(worldJson);

    // Print serialized JSON to console (optional)
    std::cout << "Serialized World:\n" << worldJson.dump(4) << std::endl;

    // Save the serialized world JSON to a file (worldtestserialize.json)
    std::ofstream outFile("worldtestserialize.json");
    if (outFile.is_open()) {
        outFile << worldJson.dump(4);  // Write with pretty formatting
        outFile.close();
        std::cout << "World serialized successfully to 'worldtestserialize.json'" << std::endl;
    }
    else {
        std::cout << "Error opening file for writing!" << std::endl;
    }

    // Clean up the created entities (if needed)
    delete entity1;  // Destructor will handle the cleanup of children and components
    delete entity2;

    return 0;
}