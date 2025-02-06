#pragma once

#include "Camera.h"
#include <GLFW/glfw3.h>

class Scene;

class Controller
{
public:
	Controller(Camera*);
	~Controller();
	void pressKey(GLFWwindow*, int);
	void mouseCallback(GLFWwindow*, double, double);
	void mouseClickCallback(GLFWwindow*, int, int, int);
	void resetMouse() { camera->setFirstMouse(true); }
	void setScene(Scene* scene) { this->scene = scene; }
	void createModelOnClick(glm::vec3 position);
private:
	Camera* camera;
	Scene* scene;

	glm::vec3 screenToWorldCoords(float, float, float, int, int);
};