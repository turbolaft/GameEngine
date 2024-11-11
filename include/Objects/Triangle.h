#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Model.h"

class Triangle : public Model
{
public:
	void createModel(const float points[], int size) override;
	void draw() override;
};
