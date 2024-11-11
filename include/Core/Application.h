#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

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
};

