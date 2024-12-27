#include "StaticMeshComponent.h"
#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <iomanip>

bool StaticMeshComponent::LoadOBJ(const std::string& filePath, std::vector<Vertex>& outVertices, std::vector<unsigned int>& outIndices, std::string& texturePath)
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
        staticMesh = new Mesh(Modelvertices, Modelindices,meshMaterial);
    }
    else
    {
        staticMesh = new Mesh(vertices, indices,meshMaterial);
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


}



