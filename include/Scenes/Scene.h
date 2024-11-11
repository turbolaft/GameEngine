#pragma once

#include "Shader.h"
#include "Model.h"
#include "Camera.h"

#include <vector>

class Scene
{
public:
	virtual void init(GLFWwindow*) = 0;
	virtual void render();
	virtual void release();
	virtual void handleInput(GLFWwindow* window);
	virtual void activate() {};
	virtual void deactivate() {};
protected:
	std::vector<Shader*> shaders;
	std::vector<Model*> models;
	GLFWwindow* window;
	Camera* camera = new Camera(glm::vec3(0.0f, 3.0f, 6.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
};

