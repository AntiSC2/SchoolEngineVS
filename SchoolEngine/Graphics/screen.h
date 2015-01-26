#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif // GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <fstream>
#include <string>
#include <stdio.h>

class Screen {
   public:
      Screen(int width, int height, const char* title);
      ~Screen();

      void render();
      void update();

      int getWidth();
      int getHeight();

   private:
      int width, height;
      SDL_Window *window;
      void initGL();
};

#endif // SCREEN_H_INCLUDED
