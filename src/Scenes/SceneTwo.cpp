#include "SceneTwo.h"

#include "Tree.h"
#include "Models/tree.h"
#include "Bush.h"
#include "Models/bushes.h"
#include "Transformation.h"
#include "TransformationComponent.h"
#include "Translate.h"
#include "Scale.h"
#include "PointLight.h"
#include "Application.h"
#include "DynamicRotate.h"
#include "Sphere.h"
#include "Models/sphere.h"
#include "DirectionalLight.h"

void SceneTwo::init(GLFWwindow* window)
{
	camera = new Camera(glm::vec3(3.0f, 10.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -10.0f);
	this->window = window;
	this->controller = new Controller(camera);

	//PointLight* pointLight = new PointLight();

	for (int i = 0; i < 50; i++) {
		shaders.push_back(new Shader("./Shaders/vertexShaderLightingPhong.glsl", "./Shaders/fragmentShaderPhongMultiple.glsl"));

		float xPos = -10.0f + (i % 10) * 8.0f;
		float zPos = 5.0f - static_cast<int>(i / 10) * 8.0f;

		float scale = 1.0f / (zPos * 0.1f);

		Transformation* transformation = new TransformationComponent();

		transformation->addChild(new Translate(glm::vec3(xPos, 0.0f, zPos)));

		if (i == 11) {
			transformation->addChild(new DynamicRotate(45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		}

		// Create and add Tree model
		Model* treeModel = new Tree();
		treeModel->createModel(tree, sizeof(float) * 556884);
		treeModel->setShader(shaders[i]);
		treeModel->setModel(transformation);
		treeModel->setProjection(camera->getProjectionMatrix());
		treeModel->setView(camera->getViewMatrix());
		treeModel->update();
		models.push_back(treeModel);

		// Create and add Bush model
		Model* bushModel = new Bush();
		bushModel->createModel(bushes, sizeof(float) * 54210);
		bushModel->setShader(shaders[i]);
		bushModel->setModel(transformation);
		bushModel->setProjection(camera->getProjectionMatrix());
		bushModel->setView(camera->getViewMatrix());
		bushModel->update();
		models.push_back(bushModel);
	}

	glm::vec3 lightPositions[] = {
		 glm::vec3(-1.0f, 3.0f, .0f),
		 glm::vec3(30.0f, 3.0f, -5.0f),
		 glm::vec3(50.0f, 3.0f, -20.0f),
		 glm::vec3(-10.0f, 3.0f, -25.0f)
	};

	for (int i = 0; i < sizeof(lightPositions) / sizeof(glm::vec3); i++) {
		Model* lightModel = new Sphere();
		lightModel->setShader(new Shader("./Shaders/vertexShaderCamera.glsl", "./Shaders/fragmentShaderSphere.glsl"));
		Transformation* transformation = new TransformationComponent();
		transformation->addChild(new Translate(lightPositions[i]));
		transformation->addChild(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
		lightModel->createModel(sphere, sizeof(float) * 17280);

		lightModel->setModel(transformation);
		lightModel->setProjection(camera->getProjectionMatrix());
		lightModel->setView(camera->getViewMatrix());
		lightModel->update();
		camera->addObserver(lightModel);

		lights.push_back(new PointLight(lightPositions[i], glm::vec3(1.0f, 1.0f, 1.0f), i, lightModel));
	}

	lights.push_back(new DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.0f, 1.0f, 0.0f), 4));

	for (auto light : lights)
	{
		for (auto model : models)
		{
			light->addObserver(model);
		}
	}

	for (auto model : models)
	{
		camera->addObserver(model);
	}
}

void SceneTwo::activate()
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void SceneTwo::deactivate()
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}