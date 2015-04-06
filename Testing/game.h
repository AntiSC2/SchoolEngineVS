#pragma once
#include "Engine.h"

class SpriteFont;
class Level;
class ParticleBatch2D;

class Game {
public:
	Game();
	~Game();

	void run();
	Engine e;
private:
	SpriteFont* spritefont = nullptr;
	ParticleBatch2D* bloodBatch;
	Level* level;
	void init();
	void quit();
	void gameLoop();
	void update();
	void draw();
};