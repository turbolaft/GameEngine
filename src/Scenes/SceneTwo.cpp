#include "SceneTwo.h"

#include "Tree.h"
#include "treeCoordinates.h"
#include "Bush.h"
#include "bushesCoordinates.h"
#include "Transformation.h"
#include "TransformationComponent.h"
#include "Translate.h"
#include "Scale.h"
#include "PointLight.h"
#include "Application.h"

void SceneTwo::init(GLFWwindow* window)
{
	camera = new Camera(glm::vec3(3.0f, 10.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -10.0f);
	this->window = window;

	//PointLight* pointLight = new PointLight();

	for (int i = 0; i < 50; i++) {
		shaders.push_back(new Shader("./Shaders/vertexShaderLightingPhong.glsl", "./Shaders/fragmentShaderPhongMultiple.glsl"));

		/*float xPos = static_cast<float>(rand() % 30 - 10);
		float zPos = static_cast<float>(rand() % 15 + 5);*/

		/*float xPos = -10.0f + i * 0.5f;
		float zPos = 10.0f - i * 0.5f;*/

		float xPos = -10.0f + (i % 10) * 8.0f;
		float zPos = 5.0f - static_cast<int>(i / 10) * 8.0f;

		float scale = 1.0f / (zPos * 0.1f);

		std::cout << "xPos: " << xPos << " zPos: " << zPos << " scale: " << scale << std::endl;

		Transformation* transformation = new TransformationComponent();
		transformation->addChild(new Translate(glm::vec3(xPos, 0.0f, zPos)));
		//transformation->addChild(new Scale(glm::vec3(scale, scale, scale)));

		// Create and add Tree model
		Model* treeModel = new Tree();
		treeModel->createModel(tree, sizeof(float) * 556884);
		treeModel->setShader(*shaders[i]);
		treeModel->setModel(transformation->execute(treeModel->getModel()));
		treeModel->setProjection(camera->getProjectionMatrix());
		treeModel->setView(camera->getViewMatrix());
		treeModel->update();
		models.push_back(treeModel);

		// Create and add Bush model
		Model* bushModel = new Bush();
		bushModel->createModel(bushes, sizeof(float) * 54210);
		bushModel->setShader(*shaders[i]);
		bushModel->setModel(transformation->execute(bushModel->getModel()));
		bushModel->setProjection(camera->getProjectionMatrix());
		bushModel->setView(camera->getViewMatrix());
		bushModel->update();
		models.push_back(bushModel);
	}

	glm::vec3 lights[4] = {
		 glm::vec3(.0f, 1.0f, .0f),
		 glm::vec3(.0f, 5.0f, .0f),
		 glm::vec3(20.0f, 10.0f, .0f),
		 glm::vec3(4.0f, 10.0f, .0f)
	};

	for (auto shader : shaders)
	{
		camera->addObserver(shader);
		//pointLight->addObserver(shader);

		for (int i = 0; i < 4; i++)
		{
			shader->update(lights[i], glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, i);
		}
	}

	//camera->addObserver(pointLight);

	/*pointLight->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	pointLight->setPosition(glm::vec3(0.0f, 10.0f, 0.0f));*/
}

void SceneTwo::render()
{
	for (int i = 0; i < models.size(); i++)
	{
		/*if (i == models.size() - 1) {
			models[i]
		}*/

		models[i]->draw();
	}
}

void SceneTwo::activate()
{
	glfwSetWindowUserPointer(window, camera);
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(this->window, [](GLFWwindow* window, double xPos, double yPos) {
		Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

		camera->mouse_callback(window, xPos, yPos);
	});
}

void SceneTwo::deactivate()
{
	glfwSetWindowUserPointer(window, nullptr);
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(this->window, nullptr);
}

void SceneTwo::handleInput(GLFWwindow* window)
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