#pragma once


#include <vector>
#include <assimp/scene.h>
#include <list>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "Helpers.h"


struct KeyPosition
{
	glm::vec3 position;
	float timeStamp;
};

struct KeyRotation
{
	glm::quat orientation;
	float timeStamp;
};

struct KeyScale
{
	glm::vec3 scale;
	float timeStamp;
};

class Bone
{
public:

	Bone(const std::string& name, int ID, const aiNodeAnim* channel);

	void Update(float animationTime);

	glm::mat4 GetLocalTransform();
	std::string GetBoneName() const;
	int GetBoneID();



	int GetPositionIndex(float animationTime);


	int GetRotationIndex(float animationTime);


	int GetScaleIndex(float animationTime);


private:

	float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);


	glm::mat4 InterpolatePosition(float animationTime);


	glm::mat4 InterpolateRotation(float animationTime);


	glm::mat4 InterpolateScaling(float animationTime);

	std::vector<KeyPosition> Positions;
	std::vector<KeyRotation> Rotations;
	std::vector<KeyScale> Scales;
	int NumPositions;
	int NumRotations;
	int NumScalings;

	glm::mat4 LocalTransform;
	std::string Name;
	int ID;
};
