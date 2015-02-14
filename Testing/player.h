#include <glm/glm.hpp>
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif
#include <gl/glew.h>

class SpriteBatch;

class Player {
public:
	Player(int x = 0, int y = 464);
	~Player();

	void update();
	void render(SpriteBatch* batch);

	bool createJab = false;
private:
	glm::ivec4 destRect;
	bool jump = false;
	int speed = 3;
	int attack = 3, defence = 3, weight = 6, wizarding = 3, yvel = 0, gravity = 2;
	GLuint texID = 0;
};