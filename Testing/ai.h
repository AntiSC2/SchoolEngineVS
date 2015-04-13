#include <Graphics/spritebatch.h>
#include <glm/glm.hpp>
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif
#include <gl/glew.h>

class ParticleBatch2D;
class Player;

class AI {
public:
	AI();
	~AI();

	void update(Player* player, ParticleBatch2D* batch);
	void render(SpriteBatch* batch);
	glm::ivec4 destRect;
	bool knockback = false;
	int xvel = 0;
private:
	int difficulty = 3, yvel = 0;
	GLuint texID;
	glm::vec2 direction;
};