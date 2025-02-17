#pragma once

#include <string>
#include <GL/glew.h>

#include "Shader.h"

class Texture {
public:
	Texture(GLenum textureTarget, const std::string& fileName);
	~Texture();
	void loadTexture(const char* path);
	void bindTexture();
	void unbindTexture();
	void deleteTexture();
	void setType(const std::string& type);
	std::string getType() { return type; }
	void bindToShader(Shader* shader, const char* uniformName, unsigned int textureUnit);
private:
	unsigned int textureID;
	std::string type;
	GLenum textureTarget;
};