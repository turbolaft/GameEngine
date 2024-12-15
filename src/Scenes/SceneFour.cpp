#include "SceneFour.h"

#include "Skybox.h"

#include "Models/skycube.h"

void SceneFour::init(GLFWwindow* window)
{
	Shader* shader = new Shader("./Shaders/vertexShaderCubemap.glsl", "./Shaders/fragmentShaderCubemap.glsl");
	this->controller = new Controller(camera);
	this->window = window;

	// Create skybox
	Skybox* skybox = new Skybox();
	skybox->loadCubemap({
		"resources/Textures/posx.jpg", // Right (Positive X)
		"resources/Textures/negx.jpg", // Left (Negative X)
		"resources/Textures/posy.jpg", // Top (Positive Y)
		"resources/Textures/negy.jpg", // Bottom (Negative Y)
		"resources/Textures/posz.jpg", // Front (Positive Z)
		"resources/Textures/negz.jpg"  // Back (Negative Z)
		});
	skybox->createModel(skycube, 108 * sizeof(float));
	skybox->setShader(shader);
	skybox->setProjection(camera->getProjectionMatrix());
	skybox->setView(camera->getViewMatrix());
	skybox->update();
	addModel(skybox);
}

void SceneFour::activate()
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void SceneFour::deactivate()
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}