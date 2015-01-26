#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include "input.h"
#include "screen.h"
#include "shader.h"
#include "sprite.h"
#include "spritebatch.h"
#include "rm.h"
#include "camera2D.h"


class Engine {
   public:

      void initSubSystems();
      void initScreen(int width, int height, const char* title);
      void initResources(const char* filePath);
      void initShaders(const char* fileVert, const char* fileFrag);


      Screen *screen;
      Camera2D *camera;
      Shader **shaders;
      SpriteBatch *TheBatch;
      Input *input;
      /*TEMP*/
      unsigned int shaderCount;
      /*TEMP*/
      Engine();
      ~Engine();

   private:
};

#endif // ENGINE_H_INCLUDED
