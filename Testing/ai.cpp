#include "ai.h"
#include <Graphics/texture.h>
#include <Managers/rm.h>
#include "player.h"
#include <Graphics/spritebatch.h>

AI::AI() {
	destRect.x = 1000;
	destRect.y = 464;
	destRect.z = 128;
	destRect.w = 256;
	texID = RM::TextureCache->createTexture("resources/textures/wizard1.png")->getID();
}

AI::~AI() {
	;
}

void AI::update(Player* player) {
	if (player->returnX() < destRect.x) {
		destRect.x -= difficulty;
	}
	if (player->returnX() > destRect.x) {
		destRect.x += difficulty;
	}
	if (knockback == true) {
		yvel = 15;
		knockback = false;
	}
	destRect.y -= yvel;
	destRect.x += xvel;
	if (xvel > 0)
		xvel -= 1;
	/*if (xvel < 0)
		xvel += 1;*/
	if (yvel > -10)
		yvel -= 1;
	if (destRect.y > 464) {
		destRect.y = 464;
		yvel = 0;
		xvel = 0;
	}
}

void AI::render(SpriteBatch* batch) {
	batch->draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texID, 0.0f, Color(255, 0, 0, 255));
}