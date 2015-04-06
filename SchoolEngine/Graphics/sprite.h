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
///This class handles a single sprite
class Sprite {
   public:
	  ///Basic constructor
      Sprite();
      ~Sprite();
	  ///Inits the sprite with coordinates, width & height, colors, and source image
      void initSprite(GLint xv, GLint yv, GLint width, GLint height, GLubyte r, GLubyte g, GLubyte b, GLubyte a, const char* filePath);
	  ///Renders the sprite to a SpriteBatch
      void render(SpriteBatch* batch);
	  ///Updates the position of the sprite
      void updatePosition(int x, int y);
   private:
	  //The coordinates, width & height is stored in this varible
      glm::vec4 destRect;
	  //The UV coordinates(UV coordinates determines how the texture is rendered on the sprite) are stored in this
      glm::vec4 uvRect;
	  //Varible that stores the color
      Color color;
	  //Pointer to the texture to use
      Texture *tex;
};

#endif // SPRITE_H_INCLUDED
