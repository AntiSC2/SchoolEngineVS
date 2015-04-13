#include "game.h"
#include <glm/glm.hpp>
#include <Managers/rm.h>
#include <Graphics/spritefont.h>
#include <Graphics/particleengine2D.h>

Game::Game() {
	;
}

Game::~Game() {
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
}

void Game::draw() {
	glActiveTexture(GL_TEXTURE0);
	e.screen->render();
	e.shaders[0]->setCameraMatrix(e.camera->getCameraMatrix());
	e.TheBatch->begin();
	e.TheBatch->end();
	e.TheBatch->renderDraw();
	e.screen->update();
}