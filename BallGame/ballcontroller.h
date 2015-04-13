#pragma once

#include <vector>
#include "ball.h"

enum class GravityDirection {NONE, LEFT, UP, RIGHT, DOWN};

class BallController {
public:
	void updateBalls(std::vector<Ball>& balls, int maxX, int maxY);
	void onMouseDown(std::vector <Ball>& balls, float mouseX, float mouseY);
	void onMouseUp(std::vector <Ball>& balls);
	void onMouseMove(std::vector <Ball>& balls, float mouseX, float mouseY);
	void setGravityDirection(GravityDirection dir);
private:
	void checkCollision(Ball& ball1, Ball& ball2);
	bool isMouseOnBall(Ball& ball, float mouseX, float mouseY);
	glm::vec2 getGravityAccel();

	int grabbedBall = -1;
	glm::vec2 prevPos = glm::vec2(0.0f, 0.0f);
	glm::vec2 grabOffset = glm::vec2(0.0f, 0.0f);

	GravityDirection gravityDirection = GravityDirection::NONE;
};

