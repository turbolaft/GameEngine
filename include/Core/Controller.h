#pragma once

#include "Camera.h"
#include <GLFW/glfw3.h>

class Controller
{
public:
	Controller(Camera*);
	~Controller();
	void pressKey(GLFWwindow*, int);
	void mouseCallback(GLFWwindow*, double, double);
	void resetMouse() { camera->setFirstMouse(true); }
private:
	Camera* camera;
};