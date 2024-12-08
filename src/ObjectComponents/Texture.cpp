#include "Texture.h"
#include "stb_image.h"

#include <iostream>

Texture::Texture(GLenum textureTarget, const std::string& fileName) {
    this->textureTarget = textureTarget;
    loadTexture(fileName.c_str());
}

void Texture::loadTexture(const char* path) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        glGenTextures(1, &textureID);
        glBindTexture(textureTarget, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }
}

Texture::~Texture() {
	deleteTexture();
}

void Texture::bindTexture() {
	glBindTexture(textureTarget, textureID);
}

void Texture::unbindTexture() {
	glBindTexture(textureTarget, 0);
}

void Texture::deleteTexture() {
	glDeleteTextures(1, &textureID);
}

void Texture::bindToShader(Shader* shader, const char* uniformName, unsigned int textureUnit) {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	this->bindTexture();
	shader->setUniform(uniformName, textureUnit);
	this->unbindTexture();
}

