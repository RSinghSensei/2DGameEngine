#pragma once
#include <glm/glm.hpp>

struct ObjTransformComponent 
{
	glm::vec3 pos{};
	glm::vec3 scale{};
	float rotation{};

	ObjTransformComponent() :pos(0), scale(0), rotation() {}

	ObjTransformComponent(const glm::vec3& objPos, const glm::vec3& objScale, float objRotation) 
	{
		pos = objPos;
		scale = objScale;
		rotation = objRotation;
	}

};
