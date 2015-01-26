#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif // GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include "spritebatch.h"
#include "vertex.h"
#include "texture.h"
#include "rm.h"

class Sprite {
   public:
      Sprite();
      ~Sprite();

      void initSprite(GLint xv, GLint yv, GLint width, GLint height, GLubyte r, GLubyte g, GLubyte b, GLubyte a, const char* filePath);
      void render(SpriteBatch* batch);
      void updatePosition(int x, int y);
   private:
      glm::vec4 destRect;
      glm::vec4 uvRect;
      Color color;
      Texture *tex;
};

#endif // SPRITE_H_INCLUDED
