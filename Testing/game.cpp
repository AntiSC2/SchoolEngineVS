#include "game.h"
#include <glm/glm.hpp>
#include <Managers/rm.h>
#include <Graphics/spritefont.h>
#include "level.h"
#include <Graphics/particleengine2D.h>

Game::Game() {
	;
}

Game::~Game() {
	spritefont->dispose();
	delete spritefont;
	spritefont = nullptr;
	delete level;
	level = nullptr;
	delete bloodEngine;
	bloodEngine = nullptr;
}

void Game::run() {
	init();
	gameLoop();
	quit();
}

void Game::init() {
	e.initSubSystems(); 
	e.initScreen(1280, 720, "TESTING");
	e.initResources("resources/data/Game.data");
	e.initShaders("resources/shaders/shader.vert", "resources/shaders/shader.frag");
	e.camera->setPosition(glm::vec2(640, 360));
	bloodEngine = new ParticleEngine2D;
	bloodBatch = new ParticleBatch2D;
	bloodBatch->initParticles(1000, 0.1f, "resources/textures/circle.png",
							  [](Particle& p){
		                                         p.position += p.velocity;
	                                             p.color.a = 255.0f / p.life; 
	});
	bloodEngine->addBatch(bloodBatch);
}

void Game::gameLoop() {
	spritefont = new SpriteFont("resources/fonts/chintzy.ttf", 64);
	hudBatch = new SpriteBatch();
	hudBatch->init();

	level = new Level(bloodBatch);

	const double dt = 16.6666666;

	uint32_t currentTime = SDL_GetTicks();
	double accumulator = 0;
	uint32_t timer = 0;
	uint16_t frames = 0, updates = 0;

	while (!e.input->windowClosed()) {
		uint32_t newTime = SDL_GetTicks();
		accumulator += newTime - currentTime;
		currentTime = newTime;
        
		while (accumulator >= dt) {
			update();
			
			accumulator -= dt;
			updates++;
		}
		draw();
		
		frames++;
		if (SDL_GetTicks() - timer > 1000) {
			printf("\nFPS: %d\nUPS: %d", frames, updates);
			frames = 0;
			updates = 0;
			timer = SDL_GetTicks();
		}
	}
}

void Game::quit() {
	;
}

void Game::update() {
	e.input->update();
	e.camera->update();
	level->update();
	bloodEngine->update();
}

void Game::draw() {
	glActiveTexture(GL_TEXTURE0);
	e.screen->render();
	e.shaders[0]->setCameraMatrix(e.camera->getCameraMatrix());
	e.TheBatch->begin();
	level->drawLevel(e.TheBatch);
	bloodEngine->render(e.TheBatch);
	//e.TheBatch->draw(glm::vec4(0, 0, 128, 256), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/wizard1.png")->getID(), 0.0f, Color(255, 255, 255, 255));
	e.TheBatch->end();
	e.TheBatch->renderDraw();
	hudBatch->begin();
	spritefont->draw(hudBatch, "the quick brown fox jumps over the lazy dog", glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), 0.0f, Color(255, 255, 255, 255));
	hudBatch->end();
	hudBatch->renderDraw();
	e.screen->update();
}