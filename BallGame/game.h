#pragma once
#include <Engine.h>

class Game {
public:
    Game();
	~Game();

	void run();
	Engine e;
private:
	void init();
	void quit();
	void gameLoop();
	void update();
	void draw();
};