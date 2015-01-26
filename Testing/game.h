#pragma once
#include "Engine.h"

class SpriteFont;

class Game {
public:
	Game();
	~Game();

	void run();
	Engine e;
private:
	SpriteFont* spritefont = nullptr;
	void init();
	void quit();
	void gameLoop();
	void update();
	void draw();
};