#ifndef SPRITEBATCH_H_INCLUDED
#define SPRITEBATCH_H_INCLUDED
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif // GLEW_STATIC
#include <GL/glew.h>
#include <algorithm>
#include <vector>
#include "Vertex.h"
///This class handles a glyph(a sprite that is going to be rendered)
class Glyph {
   public:
      Glyph() {
         ;
      }
      Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color) {
         this->depth = depth;
         this->texture = texture;
		 this->angle = 0.0f;

         this->bottomLeft.setPosition(destRect.x, destRect.y);
         this->bottomLeft.setUV(uvRect.x, uvRect.y);
         this->bottomLeft.setColor(color.r, color.g, color.b, color.a);

         this->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
         this->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
         this->bottomRight.setColor(color.r, color.g, color.b, color.a);

         this->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
         this->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
         this->topLeft.setColor(color.r, color.g, color.b, color.a);

         this->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
         this->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
         this->topRight.setColor(color.r, color.g, color.b, color.a);
      }

	  Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color, float angle) {
		  this->depth = depth;
		  this->texture = texture;
		  this->angle = 0.0f;
		  
		  glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

		  glm::vec2 tl(-halfDims.x, halfDims.y);
		  glm::vec2 bl(-halfDims.x, -halfDims.y);
		  glm::vec2 br(halfDims.x, -halfDims.y);
		  glm::vec2 tr(halfDims.x, halfDims.y);

		  tl = rotatePoint(tl, angle) + halfDims;
		  bl = rotatePoint(bl, angle) + halfDims;
		  br = rotatePoint(br, angle) + halfDims;
		  tr = rotatePoint(tr, angle) + halfDims;

		  this->bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
		  this->bottomLeft.setUV(uvRect.x, uvRect.y);
		  this->bottomLeft.setColor(color.r, color.g, color.b, color.a);

		  this->bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
		  this->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
		  this->bottomRight.setColor(color.r, color.g, color.b, color.a);

		  this->topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
		  this->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
		  this->topLeft.setColor(color.r, color.g, color.b, color.a);

		  this->topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
		  this->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		  this->topRight.setColor(color.r, color.g, color.b, color.a);
	  }

      GLuint texture;
      float depth;
	  float angle;

      Vertex topLeft;
      Vertex topRight;
      Vertex bottomLeft;
      Vertex bottomRight;
private:
	glm::vec2 rotatePoint(glm::vec2 pos, float angle) {
		glm::vec2 newW;
		newW.x = pos.x * cos(angle) - pos.y * sin(angle);
		newW.y = pos.x * sin(angle) + pos.y * cos(angle);
		return newW;
	}
};
///Enum class that says how the glyphs should be sorted
enum class GlyphSortType {
   NONE,
   FRONT_TO_BACK,
   BACK_TO_FRONT,
   TEXTURE
};
///This class handles rendering multiple glyphs
class RenderBatch {
   public:
      RenderBatch(GLuint offSet, GLuint numvertices, GLuint teXture) : offset(offSet), numVertices(numvertices), texture(teXture) {
         ;
      }
      GLuint offset;
      GLuint numVertices;
      GLuint texture;
};
///This class is the main class of the rendering process
class SpriteBatch {
   public:
	  ///Basic constructor
      SpriteBatch();
      ~SpriteBatch();
	  ///This function initializes everything for the first time
      void init();
	  ///This function cleans up the sprite batch so it's ready for a new draw call. It also determines how the glyphs are sorted
      void begin(GlyphSortType sortingType = GlyphSortType::TEXTURE);
	  ///This function makes sure the SpriteBatch is ready to render
      void end();
	  ///This function draws something to the SpriteBatch
      void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color);
	  void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color, float angle);
	  void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color, const glm::vec2& dir);
	  ///This function renders everything that has been drawn to the sprite batch to the screen
      void renderDraw();

   private:
	  //Sorts all the glyphs
      void sortGlyphs();
	  //Creates the render batches from the glyphs
      void createRenderBatches();
	  //Functions that is used to sort the glyphs
      static bool compareFrontToBack(Glyph* a, Glyph* b);
      static bool compareBackToFront(Glyph* a, Glyph* b);
      static bool compareTexture(Glyph* a, Glyph* b);
	  //Varible that stores how the glyphs should be sorted
      GlyphSortType sortType;
	  //Varible that stores pointers to the glyphs, is used for sorting
      std::vector<Glyph*> GlyphsPointers;
	  //Varible that stores the actual glyphs
      std::vector<Glyph> Glyphs;
	  //Varible that stores the render batches
      std::vector<RenderBatch> RenderBatches;
	  //Varible that stores the ID of the vertex buffer object that is used for rendering
      GLuint vboID;
	  //Varible that store the ID of the vertex array object
      GLuint vaoID;
};


#endif // SPRITEBATCH_H_INCLUDED
