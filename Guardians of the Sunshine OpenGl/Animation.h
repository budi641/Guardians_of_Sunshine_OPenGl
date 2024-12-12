#pragma once
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <functional>
#include <assimp/Importer.hpp>
#include "Helpers.h"
#include "BoneInfo.h"
#include "Bone.h"

class Model;

struct AssimpNodeData
{
	glm::mat4 transformation;
	std::string name;
	int childrenCount;
	std::vector<AssimpNodeData> children;
};

class Animation
{
public:

	Animation(std::string animationPath, Model* model);

	Bone* FindBone(const std::string& name);

	const float GetTicksPerSecond();
	const float GetDuration();
	const AssimpNodeData& GetRootNode();
	const std::map<std::string, BoneInfo>& GetBoneIDMap();


private:
	void ReadMissingBones(const aiAnimation* animation, Model& model);

	void ReadHierarchyData(AssimpNodeData& dest, const aiNode* src);

	float Duration;
	int TicksPerSecond;
	std::vector<Bone> Bones;
	AssimpNodeData RootNode;
	std::map<std::string, BoneInfo> BoneInfoMap;
};
