#pragma once
#include <glm/glm.hpp>
#include <vertex.h>
struct Ball {
	Ball(float radius, float mass, const glm::vec2& pos,
		 const glm::vec2& vel, const char* texturePath,
		 const Color& color);

	float radius;
	float mass;
	glm::vec2 vel;
	glm::vec2 pos;
	unsigned int textureID = 0;
	Color color;
};

