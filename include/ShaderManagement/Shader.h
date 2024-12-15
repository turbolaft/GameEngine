#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>

#include "Material.h"

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader(Shader& shader);
	~Shader();
	void createProgram(const char* vertex_shader, const char* fragment_shader);
	void deleteProgram();
	void use();
	void unuse();
	void setUniform(const std::string& name, glm::mat4 value);
	void setUniform(const std::string& name, glm::vec3 value);
	void setUniform(const std::string& name, float value);
	void setUniform(const std::string& name, unsigned int value);
	void setUniform(const std::string& name, Material* material);
	void update(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPosition);
	void update(const glm::vec3& position, const glm::vec3& color);
	void update(const glm::vec3& cameraPos);
	void update(const glm::vec3& position, const glm::vec3& color, int8_t type, int8_t i);
	void update(const glm::vec3& position, const glm::vec3& color, int8_t type, float cutOff, float outerCutOff);
	void update(const glm::vec3& position, const glm::vec3& color, int8_t type, float cutOff, float outerCutOff, int8_t i);
private:
	GLuint shaderProgram;

	void checkShaderCompileError(GLuint shader, const std::string& type);
};

