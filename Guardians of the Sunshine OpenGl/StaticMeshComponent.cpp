#include "StaticMeshComponent.h"
#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <iomanip>

bool StaticMeshComponent::LoadOBJ(const std::string& filePath, std::vector<Vertex>& outVertices, std::vector<unsigned int>& outIndices)
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

    vertices.clear();
    indices.clear();

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
                Vertex vertex(position,defaultColor, normal, texCoord);

                // Add vertex and index
                outVertices.push_back(vertex);
                outIndices.push_back(outVertices.size() - 1);
            }

            indexOffset += faceVertices;
        }
    }

    return true;
}

StaticMeshComponent::StaticMeshComponent(const std::string& modelPath,Material* material)
{
    name = "Mesh renderer";

    this->modelPath = modelPath;

    this->meshMaterial = material;


    if (LoadOBJ(this->modelPath, vertices, indices))
    {

        staticMesh = new Mesh(vertices, indices,meshMaterial);
    }
    else
    {
        staticMesh = new Mesh(vertices, indices, meshMaterial);
        
    }


}


Mesh* StaticMeshComponent::GetMesh() const {
    return staticMesh;
}




void StaticMeshComponent::Render(RenderManager* Renderer, glm::mat4 modelMatrix)
{
    meshMaterial->Bind(Renderer->shader);
    if (meshMaterial->shader)
    {
        Renderer->camera->UpdateProjection(*meshMaterial->shader);
        staticMesh->Draw(*meshMaterial->shader, modelMatrix);
    }
    else
    {
        Renderer->shader->Bind();
        Renderer->camera->UpdateProjection(*Renderer->shader);
        staticMesh->Draw(*Renderer->shader, modelMatrix);

    }

    meshMaterial->Unbind();
}

std::vector<unsigned int> StaticMeshComponent::GetIndices()
{
    return indices;
}

std::vector<Vertex> StaticMeshComponent::GetVertices()
{
    return vertices;
}



