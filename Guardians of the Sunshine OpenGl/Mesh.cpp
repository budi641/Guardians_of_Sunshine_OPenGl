#include "Mesh.h"
#include "Shader.h"





Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* material)
    : vertices(vertices), indices(indices), material(material) {
    setupMesh();
}

void Mesh::Draw(Shader& shader, const glm::mat4& modelMatrix, const glm::vec3& viewPos, const Light& light) {


    //shader.SetUniform("material.ambient", material->ambient);
    shader.SetUniform("material.diffuse", material->diffuse);
    shader.SetUniform("material.specular", material->specular);
   // shader.SetUniform("material.shininess", material->shininess);
    shader.SetUniform("material.alpha", material->alpha);

    shader.SetUniform("light.color", light.color);
    shader.SetUniform("light.intensity", light.intensity);
    shader.SetUniform("light.direction", light.direction);

    shader.SetUniform("viewPos", viewPos);

    shader.SetUniform("model", modelMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, material->diffuseTex);
    shader.SetUniform("material.diffuseTex", 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, material->specularTex);
    shader.SetUniform("material.specularTex", 1);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    shader.Unbind();
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);


}

bool Mesh::loadMesh(const std::string& filename, std::vector<Vertex>& vertices, std::vector<GLuint>& indices) {
   
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open obj file: " << filename << std::endl;
        return false;
    }

    std::vector<glm::vec3> tempPositions;
    std::vector<glm::vec3> tempNormals;
    std::vector<glm::vec2> tempTexCoords;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            glm::vec3 position;
            ss >> position.x >> position.y >> position.z;
            tempPositions.push_back(position);
        }
        else if (prefix == "vn") { 
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            tempNormals.push_back(normal);
        }
        else if (prefix == "vt") { 
            glm::vec2 texCoord;
            ss >> texCoord.x >> texCoord.y;
            tempTexCoords.push_back(texCoord);
        }
        else if (prefix == "f") {
            GLuint vertexIndex[3], texCoordIndex[3], normalIndex[3];
            char slash;
            for (int i = 0; i < 3; i++) {
                ss >> vertexIndex[i] >> slash >> texCoordIndex[i] >> slash >> normalIndex[i];
                
                vertexIndex[i]--;
                texCoordIndex[i]--;
                normalIndex[i]--;
            }

            
            for (int i = 0; i < 3; i++) {
                
                Color color;  

                Vertex vertex(
                    tempPositions[vertexIndex[i]],       
                    color,                         
                    tempNormals[normalIndex[i]],         
                    tempTexCoords[texCoordIndex[i]]     
                );
                vertices.push_back(vertex);
            }

            // Add the indices for this face
            indices.push_back(indices.size());
            indices.push_back(indices.size());
            indices.push_back(indices.size());
        }
    }

    file.close();
    return true;
}

