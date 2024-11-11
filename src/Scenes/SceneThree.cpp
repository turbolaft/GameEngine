#include "SceneThree.h"
#include "Sphere.h"
#include "sphereCoordinates.h"
#include "Transformation.h"
#include "TransformationComponent.h"
#include "Scale.h"
#include "Translate.h"
#include "Light.h"
#include "PointLight.h"
#include "Application.h"

void SceneThree::init(GLFWwindow* window) {
	glm::vec3 cameraPosition = glm::vec3(0.0f, 10.0f, 0.0f);
	camera = new Camera(cameraPosition, glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -90.0f);

	this->window = window;

	glm::vec3 translations[] = {
		glm::vec3(0.0f, 0.0f, 2.0f),
		glm::vec3(0.0f, 0.0f, -2.0f),
		glm::vec3(2.0f, 0.0f, 0.0f),
		glm::vec3(-2.0f, 0.0f, 0.0f)
	};

	PointLight* pointLight = new PointLight();

	for (int i = 0; i < 4; i++) {
		shaders.push_back(new Shader("./Shaders/vertexShaderLightingPhong.glsl", "./Shaders/fragmentShaderLightingPhong.glsl"));
		shaders[i]->update(cameraPosition);
		pointLight->addObserver(shaders[i]);

		Transformation* transformation = new TransformationComponent();
		transformation->addChild(new Translate(translations[i]));
		//transformation->addChild(new Scale(glm::vec3(0.7f, 0.7f, 0.7f)));

		Model* sphereModel = new Sphere();

		sphereModel->createModel(sphere, sizeof(float) * 17280);
		sphereModel->setShader(*shaders[i]);
		sphereModel->setModel(transformation->execute(sphereModel->getModel()));
		sphereModel->setProjection(camera->getProjectionMatrix());
		sphereModel->setView(camera->getViewMatrix());

		sphereModel->update();

		models.push_back(sphereModel);
		camera->addObserver(shaders[i]);
		shaders[i]->update(1.0f, 0.09f, 0.032f);
	}

	pointLight->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
}

void SceneThree::activate()
{
	glfwSetWindowUserPointer(window, camera);
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(this->window, [](GLFWwindow* window, double xPos, double yPos) {
		Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

		camera->mouse_callback(window, xPos, yPos);
	});
}

void SceneThree::deactivate()
{
	glfwSetWindowUserPointer(window, nullptr);
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(this->window, nullptr);
}

void SceneThree::handleInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->processKeyboard(FORWARD, Application::getDeltaTime() + 0.03f);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->processKeyboard(BACKWARD, Application::getDeltaTime() + 0.03f);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->processKeyboard(LEFT, Application::getDeltaTime() + 0.03f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->processKeyboard(RIGHT, Application::getDeltaTime() + 0.03f);
	}

	/*glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
		Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

		camera->processMouseMovement(xPos, yPos);
	});*/

	glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
		Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

		camera->processMouseScroll(yOffset);
	});

	/*for (auto model : models)
	{
		model->setView(camera->getViewMatrix());
	}*/
}