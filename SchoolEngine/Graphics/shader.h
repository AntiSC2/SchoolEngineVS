#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif // GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
///This class handles a single shader program
class Shader {
   public:
	  ///Basic constructor
      Shader();
      ~Shader();
	  ///Creates and compiles the shader, also preparing it for linking
      void initProgram(const char* vertPath, const char* fragPath);
	  ///Adds attributes to the shader program if the GLSL source has attributes you want to use
      void addAttribute(const char* attributeName);
	  ///Link the shader program, it's done after initProgram and addAttribute. It's now ready for use
      void linkProgram();
	  ///Get the location of a uniform in the shader
      GLuint getUniformLocation(const char* uniformName);
	  ///If the shader has a Camera uniform, you can use this function instead
      void setCameraMatrix(glm::mat4& cameraMatrix);
	  ///Sets the shader to active
      void use();
	  ///Sets the shader to unactive
      void unuse();

   private:
	  //This function actually compiles the shader, it's called inside initProgram
      void compileShader(const char* filePath, GLuint id);
	  //Varible that keeps track of how many attributes you got
      GLuint numAttributes;
	  //The program ID itself. This works like a pointer to the program
	  GLuint programID;
	  //Keeping track of the vertex and fragment shaders
      GLuint vertID, fragID;
};

#endif // SHADER_H_INCLUDED
