#include "Headers/textureClass.h"

Texture::Texture(const char* path, GLenum texType, GLenum slot, GLenum wrapS, GLenum wrapT, GLenum minFilter, GLenum magFilter) {
	type = texType;

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);
	// set the parameters
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, magFilter);
	
	stbi_set_flip_vertically_on_load(true);

	// load and generate the texture
	int width, height, nChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nChannels, 4);
	if (data) {
		GLenum formatTex = GL_RGB;
		if (nChannels == 4) formatTex = GL_RGBA;
		if (nChannels == 1) formatTex = GL_RED;

		glTexImage2D(texType, 0, formatTex, width, height, 0, formatTex, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(texType);
	}
	else {
		std::cout << "Failed to load the texture" << std::endl;
		std::cout << "stbi error: " << stbi_failure_reason() << std::endl;
	}
	
	stbi_image_free(data);
}

void Texture::setTexUnit(Shader& shader, const char* uniform, GLuint unit) {
	shader.setInt(uniform, unit);
}

void Texture::Bind() {
	glBindTexture(type, ID);
}

void Texture::Unbind() {
	glBindTexture(type, NULL);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}