#pragma once
#include <glm/glm.hpp>
#include "vertex.h"
#include "texture.h"
#include <vector>
#include <functional>

class SpriteBatch;

class Particle {
public:
	glm::vec2 position = glm::vec2(0, 0);
	glm::vec2 velocity = glm::vec2(0, 0);
	Color color = Color(255, 255, 255, 255);
	float width = 1.0f, height = 1.0f;
	float life = 0.0f;
};

inline void defaultUpdateFunc(Particle& p) {
	p.position += p.velocity;
}

class ParticleBatch2D
{
public:
	ParticleBatch2D();
	~ParticleBatch2D();

	void initParticles(int p_maxParticles, float p_decayRate,
					   const char* texture,
					   std::function<void(Particle&)> p_updateFunc = defaultUpdateFunc);
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
	std::function<void(Particle&)> updateFunc;
	Texture* particleTexture;
};

class ParticleEngine2D {
public:
	ParticleEngine2D();
	~ParticleEngine2D();
	///This function adds a batch to the engine, assumes that the batch has already been initialized.
	void addBatch(ParticleBatch2D* batch);

	void update();
	void render(SpriteBatch* batch);

private:
	std::vector<ParticleBatch2D*> batches;
};

