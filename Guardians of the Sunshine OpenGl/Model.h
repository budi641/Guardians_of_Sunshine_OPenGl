#pragma once
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "SkeletalMesh.h"
#include "shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "Helpers.h"
#include "BoneInfo.h"

class Model
{
public:
	//std::vector<Texture> textures_loaded;
	std::vector<SkeletalMesh> meshes;
	std::string directory;
	bool gammaCorrection;

	Model(std::string const& path, bool gamma = false);
	void Draw(Shader& shader ,glm::mat4 modelMatrix);

	auto& GetBoneInfoMap() { return m_BoneInfoMap; }

	int& GetBoneCount();


private:

	std::map<std::string, BoneInfo> m_BoneInfoMap;

	int m_BoneCounter = 0;

	void loadModel(std::string const& path);

	void processNode(aiNode* node, const aiScene* scene);

	void SetVertexBoneDataToDefault(Vertex& vertex);

	SkeletalMesh processMesh(aiMesh* mesh, const aiScene* scene);

	void SetVertexBoneData(Vertex& vertex, int boneID, float weight);

	void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);

	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

	/*std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);*/

};
