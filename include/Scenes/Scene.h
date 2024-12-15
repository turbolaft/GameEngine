#pragma once

#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Controller.h"
#include "Light.h"

#include <vector>

class Scene
{
public:
	virtual void init(GLFWwindow*) = 0;
	virtual void render();
	virtual void release();
	virtual void activate() {};
	virtual void deactivate() {};
	Controller* getController() { return controller; }
	void addModel(Model* model);
	void addLight(Light* light);
protected:
	std::vector<Model*> models;
	std::vector<Light*> lights;
	GLFWwindow* window;
	Camera* camera = new Camera(glm::vec3(0.0f, 3.0f, 6.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	Controller* controller;
};

