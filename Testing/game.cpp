#include "game.h"
#include <glm/glm.hpp>
#include <Managers/rm.h>
#include <Graphics/spritefont.h>

Game::Game() {
	;
}

Game::~Game() {
	delete spritefont;
	spritefont = nullptr;
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
}

void Game::gameLoop() {
	spritefont = new SpriteFont("resources/fonts/font.ttf", 64);
	while (!e.input->windowClosed()) {
		update();
		draw();
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
	spritefont->draw(e.TheBatch, "Testing", glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), 0.0f, Color(255, 255, 255, 255));
	e.TheBatch->draw(glm::vec4(200, 200, 500, 500), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/white.png")->getID(), 0.0f, Color(255, 255, 255, 255));
	e.TheBatch->end();
	e.TheBatch->renderDraw();
	e.screen->update();
}