#include "MeshRenderer.h"
#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <iomanip>

bool MeshRenderer::LoadOBJ(const std::string& filePath, std::vector<Vertex>& outVertices, std::vector<unsigned int>& outIndices, std::string& texturePath)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    // Load .obj file
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str())) {
        std::cerr << "TinyObjLoader Error: " << warn << err << std::endl;
        return false;
    }

    // Load the texture path from the first material (if any)
    if (!materials.empty() && !materials[0].diffuse_texname.empty()) {
        texturePath = materials[0].diffuse_texname;
    }
    else {
        texturePath.clear();
    }

    // Parse shapes
    for (const auto& shape : shapes) {
        size_t indexOffset = 0;

        for (size_t faceIndex = 0; faceIndex < shape.mesh.num_face_vertices.size(); faceIndex++) {
            int faceVertices = shape.mesh.num_face_vertices[faceIndex];

            for (int v = 0; v < faceVertices; v++) {
                // Access index
                tinyobj::index_t idx = shape.mesh.indices[indexOffset + v];

                // Extract position
                glm::vec3 position(
                    attrib.vertices[3 * idx.vertex_index + 0],
                    attrib.vertices[3 * idx.vertex_index + 1],
                    attrib.vertices[3 * idx.vertex_index + 2]
                );

                // Extract normal
                glm::vec3 normal(0.0f);
                if (idx.normal_index >= 0) {
                    normal = glm::vec3(
                        attrib.normals[3 * idx.normal_index + 0],
                        attrib.normals[3 * idx.normal_index + 1],
                        attrib.normals[3 * idx.normal_index + 2]
                    );
                }

                // Extract texcoord
                glm::vec2 texCoord(0.0f);
                if (idx.texcoord_index >= 0) {
                    texCoord = glm::vec2(
                        attrib.texcoords[2 * idx.texcoord_index + 0],
                        attrib.texcoords[2 * idx.texcoord_index + 1]
                    );
                }

                // Create vertex
                Color defaultColor; // Set to white
                Vertex vertex(position, defaultColor, normal, texCoord);

                // Add vertex and index
                outVertices.push_back(vertex);
                outIndices.push_back(outVertices.size() - 1);
            }

            indexOffset += faceVertices;
        }
    }

    return true;
}

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


    std::vector<Vertex> Modelvertices;
    std::vector<unsigned int> Modelindices;
    std::string texturePath;


    if ((LoadOBJ(this->modelPath, Modelvertices, Modelindices, texturePath)))
    {
        mesh = new Mesh(Modelvertices, Modelindices, new Material(diffuseTexturePath, specularTexturePath, ambient, diffuse, specular, shininess));
    }
    else
    {
        mesh = new Mesh(vertices, indices, new Material(diffuseTexturePath, specularTexturePath, ambient, diffuse, specular, shininess));
    }

    

    //mesh->material->alpha = 0.5;

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


