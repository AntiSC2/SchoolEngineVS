#ifndef CAMERA2D_H_INCLUDED
#define CAMERA2D_H_INCLUDED
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif // GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
///This class handles the camera
class Camera2D {
   public:
	  ///The camera spawns at: 0,0  which means that the center of the screen is 0,0
	  ///Basic constructor that initilazies the width and height of the camera
      Camera2D(int w, int h);
      ~Camera2D();
	  ///If you want to initialize the width and height later 
      void init(int w, int h);
	  ///Updates the camera matrix, should be called every update
      void update();
	  ///Sets the scale of all the things
      void setScale(GLfloat scale);
	  ///Sets the position of the camera
      void setPosition(glm::vec2 position);
	  ///Can be used to not render things outside the camera view
      bool cameraCulling(const glm::vec4& destRect);
	  ///Returns the current scale
      GLfloat getScale();
	  ///Returns the current position
      glm::vec2 getPosition();
	  ///Returns the current camera matrix
      glm::mat4 getCameraMatrix();
	  ///Returns the current widht
      int getWidth();
	  ///Returns the current height
      int getHeight();

   private:
	  //Varible that stores the width and height of the window
      int width, height;
	  //Varible that stores the scale of the window
      GLfloat scale;
	  //Varible that says if the camera needs to update or not
      bool needUpdate;
	  //Varible that keeps track of the position
      glm::vec2 position;
	  //The current camera matrix
      glm::mat4 cameraMatrix;
	  //Varible that stores the ortho matrix
      glm::mat4 orthoMatrix;
};

#endif // CAMERA2D_H_INCLUDED
