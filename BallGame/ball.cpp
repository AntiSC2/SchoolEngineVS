#include "ball.h"
#include <Managers\rm.h>
#include <Graphics/texture.h>


Ball::Ball(float radius, float mass, const glm::vec2& pos,
		   const glm::vec2& vel, const char* texturePath,
		   const Color& color) {
	this->radius = radius;
	this->mass = mass;
	this->pos = pos;
	this->vel = vel;
	this->textureID = RM::TextureCache->createTexture(texturePath)->getID();
	this->color = color;
}
