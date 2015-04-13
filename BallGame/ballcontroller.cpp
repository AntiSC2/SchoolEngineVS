#include "ballcontroller.h"

void BallController::updateBalls(std::vector<Ball>& balls, int maxX, int maxY) {
	const float friction = 0.001f;

	if (grabbedBall != -1) {
		balls[grabbedBall].vel = balls[grabbedBall].pos - prevPos;
	}

	glm::vec2 gravity = getGravityAccel();

	for (size_t i = 0; i < balls.size(); i++) {
		Ball& ball = balls[i];
		if (i != grabbedBall) {
			ball.pos += ball.vel;

			glm::vec2 momentumVec = ball.vel * ball.mass;
			if (momentumVec.x != 0.0f || momentumVec.y != 0.0f) {
				if (friction < glm::length(momentumVec)) {
					ball.vel -= friction * glm::normalize(momentumVec) / ball.mass;
				} else {
					ball.vel = glm::vec2(0.0f, 0.0f);
				}
			}
			ball.vel += gravity;
		}
		if (ball.pos.x < 0.0f) {
			ball.pos.x = 0.0f;
			if (ball.vel.x < 0.0f)
				ball.vel.x *= -1;
		}
	}
}
