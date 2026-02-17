#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include "shaderClass.h"

class Texture 
{
public:
	GLuint ID;
	GLuint type;
	Texture(const char* path, GLenum texType, GLenum slot, GLenum wrapS, GLenum wrapT, GLenum minFilter, GLenum magFilter);

	void setTexUnit(Shader& shader, const char* uniform, GLuint unit);

	void Bind();

	void Unbind();

	void Delete();
};
















#endif 
