#pragma once
#include <glm/glm.hpp>
#include <string>

struct SpriteComponent
{
	std::string spriteTex;
	glm::vec2 imgDimensions;

	SpriteComponent(const std::string& spriteName = "", glm::vec2 _imageDimensions = glm::vec2(0)) : spriteTex(spriteName), imgDimensions(_imageDimensions) {}

};