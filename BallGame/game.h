#pragma once
#include <Engine.h>
#include "ballcontroller.h"
#include "ball.h"
#include "ballrenderer.h"

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
	void addBall(int randX, int randY);
	BallController ballController;
	BallRenderer ballRenderer;
	std::vector<Ball> balls;
};