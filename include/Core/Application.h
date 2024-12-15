#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "Scene.h"

class Application
{
public:
	~Application();
	void init();
	void run();

	static float getDeltaTime();
private:
	GLFWwindow* window;
	static float deltaTime;
	int activeScene = 0;
	Scene* scenes[4];

	void processInput();
	void mouseCallback(GLFWwindow*, double, double);
	bool changeScene(GLFWwindow*, int);
};

