#include "jab.h"
#include <Graphics/spritebatch.h>
#include <Managers/rm.h>
#include <Graphics/texture.h>

Jab::Jab(int x, int y) {
	destRect.x = x;
	destRect.y = y;
	destRect.z = 64;
	destRect.w = 64;
	texID = RM::TextureCache->createTexture("resources/textures/jab.png")->getID();
}

Jab::~Jab() {
	;
}

void Jab::update() {
	life--;
}

void Jab::render(SpriteBatch* batch) {
	batch->draw(destRect, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), texID, 0.0f, Color(255, 255, 255, 255));
}