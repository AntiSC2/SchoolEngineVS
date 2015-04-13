#include <vector>
#include "jab.h"
#include "ai.h"
#include <Graphics/particleengine2D.h>
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif
#include <gl/glew.h>

class SpriteBatch;
class Player;

class Level {
public:
	Level(ParticleBatch2D* batch);
	~Level();
	
	void update();
	void drawLevel(SpriteBatch* batch);
private:
	GLuint backgroundID = 0;
	std::vector<Jab> jabs;
	Player* player;
	AI* ai;
	ParticleBatch2D* batchBlood = nullptr;
};