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
	int randX;
	int randY;
	for (unsigned int i = 0; i < 10; i++) {
		randX = 96 * i + 16;
		for (unsigned int y = 0; y < 10; y++) {
			randY = y * 96 + 16;
			addBall(randX, randY);
		}
	}
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
	static bool mousePressed = false;
	e.input->update();
	e.camera->update();
	if (Input::keyPressed(SDL_SCANCODE_LEFT)) {
		ballController.setGravityDirection(GravityDirection::LEFT);
	}
	else if (Input::keyPressed(SDL_SCANCODE_UP)) {
		ballController.setGravityDirection(GravityDirection::UP);
	}
	else if (Input::keyPressed(SDL_SCANCODE_RIGHT)) {
		ballController.setGravityDirection(GravityDirection::RIGHT);
	}
	else if (Input::keyPressed(SDL_SCANCODE_DOWN)) {
		ballController.setGravityDirection(GravityDirection::DOWN);
	}
	if (Input::mousePressed(SDL_BUTTON_LEFT) && mousePressed == false) {
		ballController.onMouseDown(balls, Input::getMouseX(e.camera), Input::getMouseY(e.camera));
		mousePressed = 1;
	}
	if (mousePressed && Input::mousePressed(SDL_BUTTON_LEFT) == 0) {
		ballController.onMouseUp(balls);
		mousePressed = 0;
	}
	if (Input::getMouseMove()) {
		ballController.onMouseMove(balls, Input::getMouseX(e.camera), Input::getMouseY(e.camera));
	}
	ballController.updateBalls(balls, 1280, 720);
}

void Game::draw() {
	glActiveTexture(GL_TEXTURE0);
	e.screen->render();
	e.shaders[0]->setCameraMatrix(e.camera->getCameraMatrix());
	e.TheBatch->begin();
	for (size_t i = 0; i < balls.size(); i++)
	    ballRenderer.renderBall(e.TheBatch, balls[i]);
	e.TheBatch->end();
	e.TheBatch->renderDraw();
	e.screen->update();
}

void Game::addBall(int randX, int randY) {

	int randR = rand() % 16 + 16;
	int randM = rand() % 10 + randR;

	balls.emplace_back(randR, randM, glm::vec2((float)randX, (float)randY), glm::vec2(0.0f, 0.0f), "resources/textures/circle.png", Color(255, 255, 255, 255));
}