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
		if (ball.pos.x - ball.radius < 0.0f) {
			ball.pos.x = ball.radius;
			if (ball.vel.x < 0.0f)
				ball.vel.x *= -1;
		}
		else if (ball.pos.x + ball.radius >= float(maxX)) {
			ball.pos.x = (float)maxX - ball.radius;
			if (ball.vel.x > 0.0f) {
				ball.vel.x *= -1;
			}
		}
		if (ball.pos.y < 0.0f) {
			ball.pos.y = 0.0f;
			if (ball.vel.y < 0.0f) {
				ball.vel.y *= -1.0f;
			}
		}
		else if (ball.pos.y + ball.radius >= float(maxY)) {
			ball.pos.y = (float)maxY - ball.radius;
			if (ball.vel.y > 1.0f) {
				ball.vel.y *= 1.0f;
			}
		}
		
		for (size_t j = i + 1; j < balls.size(); j++) {
			checkCollision(ball, balls[j]);
		}
	}

	if (grabbedBall != -1) {
		balls[grabbedBall].vel = balls[grabbedBall].pos - prevPos;
		prevPos = balls[grabbedBall].pos;
	}
}

void BallController::onMouseDown(std::vector<Ball>& balls, float mouseX, float mouseY) {
	for (size_t i = 0; i < balls.size(); i++) {
		if (isMouseOnBall(balls[i], mouseX, mouseY)) {
			grabbedBall = i;
			grabOffset = glm::vec2(mouseX, mouseY) - balls[i].pos;
			prevPos = balls[i].pos;
			balls[i].vel = glm::vec2(0.0f, 0.0f);
		}
	}
}

void BallController::onMouseUp(std::vector<Ball>& balls) {
	if (grabbedBall != -1) {
		balls[grabbedBall].vel = balls[grabbedBall].pos - prevPos;
	    grabbedBall = -1;
	}
}

void BallController::onMouseMove(std::vector<Ball>& balls, float mouseX, float mouseY) {
	if (grabbedBall != -1) {
		balls[grabbedBall].pos = glm::vec2(mouseX, mouseY) - grabOffset;
	}
}

void BallController::setGravityDirection(GravityDirection dir) {
	gravityDirection = dir;
}

void BallController::checkCollision(Ball& ball1, Ball& ball2) {
	// We add radius since position is the top left corner
	glm::vec2 distVec = (ball2.pos) -
		(ball1.pos);
	glm::vec2 distDir = glm::normalize(distVec);
	float dist = glm::length(distVec);
	float totalRadius = ball1.radius + ball2.radius;

	float collisionDepth = totalRadius - dist;
	// Check for collision
	if (collisionDepth > 0) {

		// Push away the less massive one
		if (ball1.mass < ball2.mass) {
			ball1.pos -= distDir * collisionDepth;
		}
		else {
			ball2.pos += distDir * collisionDepth;
		}

		// Calculate deflection. http://stackoverflow.com/a/345863
		float aci = glm::dot(ball1.vel, distDir) / ball2.mass;
		float bci = glm::dot(ball2.vel, distDir) / ball1.mass;

		float massRatio = ball1.mass / ball2.mass;

		ball1.vel += (bci - aci) * distDir * (1.0f / massRatio);
		ball2.vel += (aci - bci) * distDir * massRatio;
	}
}

bool BallController::isMouseOnBall(Ball&b, float mouseX, float mouseY) {
	return (mouseX >= b.pos.x - b.radius && mouseX < b.pos.x + b.radius &&
			mouseY >= b.pos.y - b.radius && mouseY < b.pos.y + b.radius);
}

glm::vec2 BallController::getGravityAccel() {
	const float GRAVITY_FORCE = 0.1f;
	glm::vec2 gravity;

	switch (gravityDirection) {
		case GravityDirection::DOWN:
			gravity = glm::vec2(0.0f, GRAVITY_FORCE);
			break;
		case GravityDirection::LEFT:
			gravity = glm::vec2(-GRAVITY_FORCE, 0.0f);
			break;
		case GravityDirection::RIGHT:
			gravity = glm::vec2(GRAVITY_FORCE, 0.0f);
			break;
		case GravityDirection::UP:
			gravity = glm::vec2(0.0f, -GRAVITY_FORCE);
			break;
		default:
			gravity = glm::vec2(0.0f);
			break;
	}
	return gravity;
}