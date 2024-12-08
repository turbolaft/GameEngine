#include "SceneThree.h"
#include "Sphere.h"
#include "Models/sphere.h"
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
	this->controller = new Controller(camera);

	this->window = window;

	glm::vec3 translations[] = {
		glm::vec3(0.0f, 0.0f, 2.0f),
		glm::vec3(0.0f, 0.0f, -2.0f),
		glm::vec3(2.0f, 0.0f, 0.0f),
		glm::vec3(-2.0f, 0.0f, 0.0f)
	};

	for (int i = 0; i < 4; i++) {
		Shader* shader = new Shader("./Shaders/vertexShaderLightingPhong.glsl", "./Shaders/fragmentShaderLightingPhong.glsl");
		shader->update(cameraPosition);

		Transformation* transformation = new TransformationComponent();
		transformation->addChild(new Translate(translations[i]));
		//transformation->addChild(new Scale(glm::vec3(0.7f, 0.7f, 0.7f)));

		Model* sphereModel = new Sphere();

		sphereModel->createModel(sphere, sizeof(float) * 17280);
		sphereModel->setShader(shader);
		sphereModel->setModel(transformation);
		sphereModel->setProjection(camera->getProjectionMatrix());
		sphereModel->setView(camera->getViewMatrix());
		sphereModel->update();

		this->addModel(sphereModel);
	}

	PointLight* pointLight = new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	this->addLight(pointLight);
}

void SceneThree::activate()
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void SceneThree::deactivate()
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}