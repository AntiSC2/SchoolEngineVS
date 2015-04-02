#include "level.h"
#include "player.h"
#include <Managers/rm.h>
#include <Graphics/texture.h>
#include <Graphics/spritebatch.h>

Level::Level() {
	player = new Player(576, 464);
	backgroundID = RM::TextureCache->createTexture("resources/textures/jab.png")->getID();
	ai = new AI;
}

Level::~Level() {
	delete player;
	player = nullptr;
}

void Level::update() {
	player->update();
	ai->update(player);
	if (player->createJab) {
		player->createJab = false;
		if (player->direction == 1)
		    jabs.emplace_back(player->returnX() + 128, player->returnY() + 64);
		else if (player->direction == 0)
			jabs.emplace_back(player->returnX() - 64, player->returnY() + 64);
	}
	for (int i = 0; i < jabs.size(); i++) {
		jabs[i].update();
		if (jabs[i].destRect.x + jabs[i].destRect.z > ai->destRect.x) {
			if (jabs[i].destRect.x < ai->destRect.x + ai->destRect.z) {
				if (jabs[i].destRect.y + jabs[i].destRect.w > ai->destRect.y) {
					if (jabs[i].destRect.y < ai->destRect.y + ai->destRect.w) {
						ai->knockback = true;
						if (player->direction == 1)
							ai->xvel = 15;
						else
							ai->xvel = -15;
					}

				}
			}
		}
		if (jabs[i].life < 1) {
			jabs[i] = jabs.back();
			jabs.pop_back();
			i--;
		}
	}
}

void Level::drawLevel(SpriteBatch* batch) {
	//batch->draw(glm::vec4(0.0f, 0.0f, 1280.0f, 720.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), backgroundID, 0.0f, Color(255, 255, 255, 255));
	player->render(batch);
	ai->render(batch);
	for (int i = 0; i < jabs.size(); i++) {
		jabs[i].render(batch);
	}
}