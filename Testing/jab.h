#include <glm/glm.hpp>
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif
#include <gl/glew.h>

class SpriteBatch;

class Jab {
public:
	Jab(int x, int y);
	~Jab();

	void update();
	void render(SpriteBatch* batch);
	int life = 10;
	glm::ivec4 destRect;
private:
	GLuint texID;
};