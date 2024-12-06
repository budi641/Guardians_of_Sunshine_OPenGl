#include "MeshRenderer.h"
#include <iostream>
#include <iomanip>

MeshRenderer::MeshRenderer(const std::string& modelPath,
    const std::string& diffuseTexturePath,
    const std::string& specularTexturePath,
    const glm::vec3& ambient,
    const glm::vec3& diffuse,
    const glm::vec3& specular,
    float shininess)
{
    name = "Mesh renderer";

    this->modelPath = modelPath;

    std::vector<Vertex> vertices = {

        {{-0.5f, -0.5f,  0.5f}, {}, {0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}}, 
        {{ 0.5f, -0.5f,  0.5f}, {}, {0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}}, 
        {{ 0.5f,  0.5f,  0.5f}, {}, {0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}}, 
        {{-0.5f,  0.5f,  0.5f}, {}, {0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}}, 

        {{ 0.5f, -0.5f, -0.5f}, {}, {0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}}, 
        {{-0.5f, -0.5f, -0.5f}, {}, {0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}}, 
        {{-0.5f,  0.5f, -0.5f}, {}, {0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}}, 
        {{ 0.5f,  0.5f, -0.5f}, {}, {0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}}, 

  
        {{-0.5f, -0.5f, -0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, 
        {{-0.5f, -0.5f,  0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}}, 
        {{-0.5f,  0.5f,  0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}}, 
        {{-0.5f,  0.5f, -0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}}, 

   
        {{ 0.5f, -0.5f,  0.5f}, {}, {1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, 
        {{ 0.5f, -0.5f, -0.5f}, {}, {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}}, 
        {{ 0.5f,  0.5f, -0.5f}, {}, {1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}}, 
        {{ 0.5f,  0.5f,  0.5f}, {}, {1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}}, 


        {{-0.5f,  0.5f,  0.5f}, {}, {0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, 
        {{ 0.5f,  0.5f,  0.5f}, {}, {0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}}, 
        {{ 0.5f,  0.5f, -0.5f}, {}, {0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}}, 
        {{-0.5f,  0.5f, -0.5f}, {}, {0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}},


        {{-0.5f, -0.5f, -0.5f}, {}, {0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, 
        {{ 0.5f, -0.5f, -0.5f}, {}, {0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}}, 
        {{ 0.5f, -0.5f,  0.5f}, {}, {0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}}, 
        {{-0.5f, -0.5f,  0.5f}, {}, {0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}}, 
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,       
        4, 5, 6, 6, 7, 4,       
        8, 9, 10, 10, 11, 8,    
        12, 13, 14, 14, 15, 12, 
        16, 17, 18, 18, 19, 16, 
        20, 21, 22, 22, 23, 20  
    };

    mesh = new Mesh(vertices, indices, new Material(diffuseTexturePath, specularTexturePath, ambient, diffuse, specular, shininess));

}


Mesh* MeshRenderer::GetMesh() const {
    return mesh;
}

Material* MeshRenderer::GetMaterial() const {
    return mesh->material;
}


const std::string& MeshRenderer::GetModelPath() const {
    return modelPath;
}


const glm::vec3& MeshRenderer::GetAmbient() const {
    return mesh->material->ambient;
}



const glm::vec3& MeshRenderer::GetDiffuse() const {
    return mesh->material->diffuse;
}



const glm::vec3& MeshRenderer::GetSpecular() const {
    return mesh->material->specular;
}



float MeshRenderer::GetShininess() const {
    return mesh->material->shininess;
}



void MeshRenderer::Render(RenderManager* Renderer, glm::mat4 modelMatrix)
{
    //glm::mat4 matrix = modelMatrix;

    //std::cout << std::fixed << std::setprecision(2);
    //for (int row = 0; row < 4; ++row) {
    //    for (int col = 0; col < 4; ++col) {
    //        std::cout << std::setw(8) << matrix[row][col] << " ";
    //    }
    //    std::cout << std::endl;
    //}
    /*std::cout << std::endl;*/


    mesh->Draw(*Renderer->shader, modelMatrix, Renderer->camera->GetPosition(), *Renderer->light);
}

void MeshRenderer::Serialize(nlohmann::json& jsonData) const {

}

void MeshRenderer::Deserialize(const nlohmann::json& jsonData) {


}


