#include "MeshRenderer.h"
#include <iostream>
#include <iomanip>
#include<json/json.h>
using json = nlohmann::json;
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
    jsonData["type"] = "MeshRenderer Component";

        jsonData["modelPath"] = modelPath;
        jsonData["diffuseTexturePath"] = mesh->material->diffusePath;
        jsonData["specularTexturePath"] = mesh->material->specularPath;

        jsonData["ambient"] = { mesh->material->ambient.x, mesh->material->ambient.y, mesh->material->ambient.z };
        jsonData["diffuse"] = { mesh->material->diffuse.x, mesh->material->diffuse.y, mesh->material->diffuse.z };
        jsonData["specular"] = { mesh->material->specular.x, mesh->material->specular.y, mesh->material->specular.z };

        jsonData["shininess"] = mesh->material->shininess;
    }



void MeshRenderer::Deserialize(const nlohmann::json& jsonData) {
    // Deserialize model path
    std::string modelPath = jsonData.contains("modelPath") ? jsonData["modelPath"] : "";

    // Deserialize material properties
    glm::vec3 ambient(0.0f), diffuse(0.0f), specular(0.0f);
    float shininess = 0.0f;

    if (jsonData.contains("ambient")) {
        ambient = glm::vec3(
            jsonData["ambient"][0],
            jsonData["ambient"][1],
            jsonData["ambient"][2]
        );
    }

    if (jsonData.contains("diffuse")) {
        diffuse = glm::vec3(
            jsonData["diffuse"][0],
            jsonData["diffuse"][1],
            jsonData["diffuse"][2]
        );
    }

    if (jsonData.contains("specular")) {
        specular = glm::vec3(
            jsonData["specular"][0],
            jsonData["specular"][1],
            jsonData["specular"][2]
        );
    }

    if (jsonData.contains("shininess")) {
        shininess = jsonData["shininess"];
    }

    // Deserialize texture paths
    std::string diffuseTexturePath = jsonData.contains("diffuseTexturePath") ? jsonData["diffuseTexturePath"] : "";
    std::string specularTexturePath = jsonData.contains("specularTexturePath") ? jsonData["specularTexturePath"] : "";

    // Reinitialize MeshRenderer
    *this = MeshRenderer(modelPath, diffuseTexturePath, specularTexturePath, ambient, diffuse, specular, shininess);
}

