#include "particleengine2D.h"
#include "SpriteBatch.h"
#include "rm.h"

void Particle::update() {
	position += velocity;
}

ParticleBatch2D::ParticleBatch2D() {
	particleTexture = RM::TextureCache->createTexture("resources/textures/white.png");
}


ParticleBatch2D::~ParticleBatch2D() {
	delete[] myParticles;
}

void ParticleBatch2D::initParticles(int p_maxParticles, float p_decayRate) {
	maxParticles = p_maxParticles;
	decayRate = p_decayRate;

	myParticles = new Particle[maxParticles];
}

void ParticleBatch2D::update() {
	for (int i = 0; i < maxParticles; i++) {
		if (myParticles[i].life > 0.0f) {
			myParticles[i].update();
			myParticles[i].life -= decayRate;
		}
	}
}

void ParticleBatch2D::render(SpriteBatch* batch) {
	for (int i = 0; i < maxParticles; i++) {
		if (myParticles[i].life > 0.0f){
			batch->draw(glm::vec4(myParticles[i].position.x - myParticles[i].width / 2,
				        myParticles[i].position.y - myParticles[i].height / 2,
						myParticles[i].width, myParticles[i].height),
						glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), particleTexture->getID(), 0.0f, myParticles[i].color);
		}
	}
}

void ParticleBatch2D::addParticle(const glm::vec2& position, const glm::vec2& velocity, float width, float height, const Color& color) {
	for (int i = lastActiveParticle; i < maxParticles; i++) {
		if (myParticles[i].life > 0.0f) {
			;
		}
		else {
			myParticles[i].life = 1.0f;
			myParticles[i].position = position;
			myParticles[i].velocity = velocity;
			myParticles[i].width = width;
			myParticles[i].height = height;
			myParticles[i].color = color;
			lastActiveParticle = i;
			return;
		}
	}
	for (int i = 0; i < lastActiveParticle; i++) {
		if (myParticles[i].life > 0.0f) {
			;
		}
		else {
			myParticles[i].life = 1.0f;
			myParticles[i].position = position;
			myParticles[i].velocity = velocity;
			myParticles[i].width = width;
			myParticles[i].height = height;
			myParticles[i].color = color;
			lastActiveParticle = i;
			return;
		}
	}
	printf("Particle Batch is full!");
	lastActiveParticle = 0;
	myParticles[0].life = 1.0f;
	myParticles[0].position = position;
	myParticles[0].velocity = velocity;
	myParticles[0].width = width;
	myParticles[0].height = height;
	myParticles[0].color = color;
}

ParticleEngine2D::ParticleEngine2D() {
	;
}

ParticleEngine2D::~ParticleEngine2D() {
	for (const auto& p : batches) {
		delete p;
	}
}

void ParticleEngine2D::addBatch(ParticleBatch2D* batch) {
	batches.push_back(batch);
}

void ParticleEngine2D::update() {
	for (const auto& p : batches) {
		p->update();
	}
}

void ParticleEngine2D::render(SpriteBatch* batch) {
	for (const auto& p : batches) {
		p->render(batch);
	}
}
