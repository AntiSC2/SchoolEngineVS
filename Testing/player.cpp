#include "player.h"
#include <Graphics/spritebatch.h>
#include <Managers/RM.h>
#include <Graphics/texture.h>
#include <input.h>

Player::Player(int x, int y) {
	destRect.x = x;
	destRect.y = y;
	destRect.z = 128;
	destRect.w = 256;
	texID = RM::TextureCache->createTexture("resources/textures/wizard1.png")->getID();
}

Player::~Player() {
	;
}

void Player::update() {
	if (Input::keyPressed(SDL_SCANCODE_D)) {
		destRect.x += 1 * speed;
		direction = 1;
	}
	if (Input::keyPressed(SDL_SCANCODE_A)) {
		destRect.x -= 1 * speed;
		direction = 0;
	}
	if (Input::keyPressed(SDL_SCANCODE_W) && jump == false) {
		jump = true;
		yvel = -50 + (weight * 5);
	}
	if (Input::keyTyped(SDL_SCANCODE_SPACE) && createJab == false && jabCoolDown == 0) {
		createJab = true;
		jabCoolDown = 10;
	}
	if (jabCoolDown > 0) {
		jabCoolDown--;
	}
	destRect.y += yvel;
	yvel += gravity;
	if (destRect.y > 464) {
		destRect.y = 464;
		yvel = 0;
		jump = false;
	}
}

void Player::render(SpriteBatch* batch) {
	batch->draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texID, 0.0f, Color(255, 255, 255, 255));
	//batch->draw(glm::ivec4(0, 0 , 256, 256), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texID, 0.0f, Color(255, 255, 255, 255));
}

int Player::returnX() {
	return destRect.x;
}

int Player::returnY() {
	return destRect.y;
}