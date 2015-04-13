#pragma once
#include "ball.h"

class SpriteBatch;

class BallRenderer {
public:
	void renderBall(SpriteBatch* batch, Ball& ball);
};

