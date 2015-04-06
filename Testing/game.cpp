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
	delete spritefont;
	spritefont = nullptr;
	delete level;
	level = nullptr;
	delete bloodBatch;
	bloodBatch = nullptr;
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
}

void Game::gameLoop() {
	spritefont = new SpriteFont("resources/fonts/font.ttf", 64);
	bloodBatch = new ParticleBatch2D;
	bloodBatch->initParticles(1000, 0.1f);
	level = new Level;

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
	bloodBatch->addParticle(glm::vec2(500, 300), glm::vec2(rand()%20 - 10, rand()%20 - 10), 5, 5, Color(180, 0, 0, 255));
	bloodBatch->update();
	level->update();
}

void Game::draw() {
	glActiveTexture(GL_TEXTURE0);
	e.screen->render();
	e.shaders[0]->setCameraMatrix(e.camera->getCameraMatrix());
	e.TheBatch->begin();
	level->drawLevel(e.TheBatch);
	bloodBatch->render(e.TheBatch);
	//spritefont->draw(e.TheBatch, "Testing", glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), 0.0f, Color(255, 255, 255, 255));
	//e.TheBatch->draw(glm::vec4(0, 0, 128, 256), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/wizard1.png")->getID(), 0.0f, Color(255, 255, 255, 255));
	e.TheBatch->end();
	e.TheBatch->renderDraw();
	e.screen->update();
}