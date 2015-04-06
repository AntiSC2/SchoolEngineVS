#pragma once
#include <glm/glm.hpp>
#include "vertex.h"
#include "texture.h"

class SpriteBatch;

class Particle {
	friend class ParticleBatch2D;
public:
	void update();
private:
	glm::vec2 position = glm::vec2(0, 0);
	glm::vec2 velocity = glm::vec2(0, 0);
	Color color = Color(255, 255, 255, 255);
	float width = 1.0f, height = 1.0f;
	float life = 0.0f;
};

class ParticleBatch2D
{
public:
	ParticleBatch2D();
	~ParticleBatch2D();

	void initParticles(int p_maxParticles, float p_decayRate);
	void update();
	void render(SpriteBatch* batch);
	void addParticle(const glm::vec2& position,
					 const glm::vec2& velocity,
					 float width,
					 float height,
					 const Color& color);

private:
	Particle* myParticles = nullptr;
	float decayRate = 0.1f;
	int maxParticles;
	int lastActiveParticle = 0;
	Texture* particleTexture;
};

class ParticleEngine2D

