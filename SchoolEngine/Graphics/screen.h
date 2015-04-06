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
///This class handles the window itself
class Screen {
   public:
	   ///Constructor that initilazies the basic window properties like Width, Height and the name of the window
      Screen(int width, int height, const char* title);
      ~Screen();
	  ///Clears the screen
      void render();
	  ///Updates the window to display the new framebuffer
      void update();
	  ///Return the width of the window
      int getWidth();
	  ///Return the height of the window
      int getHeight();

   private:
	  //Varibles to store the width and height
      int width, height;
	  //The pointer to the actual window
      SDL_Window *window;
	  //Initilazies OpenGL(Must be done here because OpenGL needs an OpenGL_Context and that requires the pointer to the window)
      void initGL();
};

#endif // SCREEN_H_INCLUDED
