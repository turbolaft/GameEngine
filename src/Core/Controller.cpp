#include "Controller.h"

#include "Application.h"

Controller::Controller(Camera* camera)
{
	this->camera = camera;
}

Controller::~Controller()
{
}

void Controller::pressKey(GLFWwindow* window, int key)
{
	switch (key) {
		case GLFW_KEY_W:
			camera->processKeyboard(FORWARD, Application::getDeltaTime() + 0.03f);
			break;
		case GLFW_KEY_S:
			camera->processKeyboard(BACKWARD, Application::getDeltaTime() + 0.03f);
			break;
		case GLFW_KEY_A:
			camera->processKeyboard(LEFT, Application::getDeltaTime() + 0.03f);
			break;
		case GLFW_KEY_D:
			camera->processKeyboard(RIGHT, Application::getDeltaTime() + 0.03f);
			break;
	}
}

void Controller::mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	camera->mouse_callback(window, xPos, yPos);
}