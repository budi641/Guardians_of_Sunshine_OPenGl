#include "MeshRenderer.h"
#include <iostream>
#include <iomanip>

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material)
{

    this->mesh = mesh;
    this->material = material;

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


