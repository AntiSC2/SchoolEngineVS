#include "ballrenderer.h"
#include <Graphics/spritebatch.h>
#include <glm/glm.hpp>

void BallRenderer::renderBall(SpriteBatch* batch, Ball& ball) {
	batch->draw(glm::vec4(ball.pos.x - ball.radius, ball.pos.y - ball.radius, 2 * ball.radius, 2 * ball.radius),
				glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), ball.textureID, 0.0f, ball.color);
}