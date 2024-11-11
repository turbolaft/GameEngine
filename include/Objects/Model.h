#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "DrawableObject.h"

class Model : public DrawableObject
{
public:
	virtual ~Model();
	virtual void createModel(const float points[], int size) = 0;
	virtual void deleteModel();
protected:
	GLuint VBO, VAO;
};

