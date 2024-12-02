#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include "World.h"
#include "Entity.h"
#include "TransformComponent.h"


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

    World world;

 
    Entity ameen("ameen");

    Entity test("test");

    ameen.GetTransformComponent()->SetPosition(glm::vec3(3, 5, 8));

    ameen.AddChild(&test);

    test.GetTransformComponent()->SetPosition(glm::vec3(5, 6, 7));

    world.AddEntity(&ameen);

    world.GetWorldMatrix(&ameen);


    PrintMat4(world.GetWorldMatrix(&test));



    return 0;
}
