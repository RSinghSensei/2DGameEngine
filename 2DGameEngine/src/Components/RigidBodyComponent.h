#pragma once
#include <glm/glm.hpp>


struct RigidBodyComponent
{
	glm::vec2 velocity;

	RigidBodyComponent(const glm::vec2& velocityVal) :velocity(velocityVal) {}
	RigidBodyComponent() :velocity(0) {}

};