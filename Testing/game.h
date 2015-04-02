#pragma once
#include "Engine.h"

class SpriteFont;
class Level;

class Game {
public:
	Game();
	~Game();

	void run();
	Engine e;
private:
	SpriteFont* spritefont = nullptr;
	Level* level;
	void init();
	void quit();
	void gameLoop();
	void update();
	void draw();
};