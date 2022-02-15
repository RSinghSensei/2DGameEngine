#pragma once
#include <glm/glm.hpp>


struct RigidBodyComponent
{
	glm::vec2 objVelocity;

	RigidBodyComponent(const glm::vec2& velocity) : objVelocity(velocity) {}
	RigidBodyComponent() :objVelocity(0) {}

};