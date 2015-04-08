#pragma once
#include "Engine.h"

class SpriteFont;
class Level;
class ParticleBatch2D;
class ParticleEngine2D;

class Game {
public:
	Game();
	~Game();

	void run();
	Engine e;
private:
	SpriteBatch* hudBatch;
	SpriteFont* spritefont = nullptr;
	ParticleBatch2D* bloodBatch;
	ParticleEngine2D* bloodEngine;
	Level* level;
	void init();
	void quit();
	void gameLoop();
	void update();
	void draw();
};