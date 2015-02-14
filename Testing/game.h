#pragma once
#include "Engine.h"

class SpriteFont;
class Player;

class Game {
public:
	Game();
	~Game();

	void run();
	Engine e;
private:
	SpriteFont* spritefont = nullptr;
	Player* player;
	void init();
	void quit();
	void gameLoop();
	void update();
	void draw();
};