#include <vector>
#include "jab.h"
#include "ai.h"
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif
#include <gl/glew.h>

class SpriteBatch;
class Player;

class Level {
public:
	Level();
	~Level();
	
	void update();
	void drawLevel(SpriteBatch* batch);
private:
	GLuint backgroundID = 0;
	std::vector<Jab> jabs;
	Player* player;
	AI* ai;
};