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
#include "DynamicTranslate.h"
#include "Sphere.h"
#include "Models/sphere.h"
#include "DirectionalLight.h"
#include "Rectangle.h"
#include "Models/rectangle.h"
#include "Material.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void SceneTwo::init(GLFWwindow* window)
{
	camera = new Camera(glm::vec3(10.0f, 15.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -45.0f);
	camera->setCutoff(glm::cos(glm::radians(12.5f)));
	camera->setOuterCutoff(glm::cos(glm::radians(20.0f)));
	camera->setLightIterator(5);
	camera->setLight(true);
	this->window = window;
	this->controller = new Controller(camera);

	Material* treeMaterial = new Material(
		glm::vec3(0.05f, 0.035f, 0.02f), // Ambient (darker brown)
		glm::vec3(0.03f, 0.2f, 0.1f),    // Diffuse (moderate brown)
		glm::vec3(0.05f, 0.05f, 0.05f),  // Specular (almost none)
		64.0f                            // Shininess (rough surface)
	);
	Material* bushMaterial = new Material(
		glm::vec3(0.0f, 0.1f, 0.0f),   // Ambient (dark green)
		glm::vec3(0.2f, 0.5f, 0.2f),   // Diffuse (vibrant green)
		glm::vec3(0.1f, 0.3f, 0.1f),   // Specular (slightly glossy)
		16.0f                           // Shininess (smooth leaves)
	);

	for (int i = 0; i < 50; i++) {
		Shader* shader = new Shader("./Shaders/vertexShaderLightingPhong.glsl", "./Shaders/fragmentShaderPhongMultiple.glsl");

		float xPos = -10.0f + (i % 10) * 8.0f;
		float zPos = 5.0f - static_cast<int>(i / 10) * 8.0f;

		float scale = 1.0f / (zPos * 0.1f);

		Transformation* transformation = new TransformationComponent();

		transformation->addChild(new Translate(glm::vec3(xPos, 0.0f, zPos)));

		if (i == 11) {
			transformation->addChild(new DynamicRotate(45.0f, glm::vec3(0.0f, 1.0f, 0.0f), 0.8f));
		}

		// Create and add Tree model
		Model* treeModel = new Tree();
		treeModel->createModel(tree, sizeof(float) * 556884);
		treeModel->setShader(shader);
		treeModel->setModel(transformation);
		treeModel->setProjection(camera->getProjectionMatrix());
		treeModel->setView(camera->getViewMatrix());
		treeModel->update();
		treeModel->setMaterial(treeMaterial);
		treeModel->setLightModel(PHONG);
		this->addModel(treeModel);

		Shader* bushShader = new Shader("./Shaders/vertexShaderLightingPhong.glsl", "./Shaders/fragmentShaderPhongMultiple.glsl");

		Model* bushModel = new Bush();
		bushModel->createModel(bushes, sizeof(float) * 54210);
		bushModel->setShader(bushShader);
		bushModel->setModel(transformation);
		bushModel->setProjection(camera->getProjectionMatrix());
		bushModel->setView(camera->getViewMatrix());
		bushModel->update();
		bushModel->setMaterial(bushMaterial);
		bushModel->setLightModel(BLINN_PHONG);
		this->addModel(bushModel);
	}

	Texture* texture = new Texture(GL_TEXTURE_2D, "./resources/Textures/grass.png");
	Model* rect = new Rectangle();
	Transformation* rectTransformation = new TransformationComponent();
	rectTransformation->addChild(new Translate(glm::vec3(26.0f, 0.0f, -11.0f)));
	rectTransformation->addChild(new Rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
	rectTransformation->addChild(new Scale(glm::vec3(80.0f, 50.0f, 1.0f)));
	rect->createModel(rectangle, sizeof(float) * 32);
	rect->setUpModel(new Shader("./Shaders/vertexShaderTexturePhong.glsl", "./Shaders/fragmentShaderTextureMultiple.glsl"),
		camera, rectTransformation, texture);
	this->addModel(rect);
	camera->addObserver((LightObserver*)rect);

	glm::vec3 lightPositions[] = {
		 glm::vec3(-1.0f, 3.0f, .0f),
		 glm::vec3(30.0f, 3.0f, -5.0f),
		 glm::vec3(50.0f, 3.0f, -22.0f),
		 glm::vec3(-10.0f, 3.0f, -25.0f)
	};

	for (int i = 0; i < sizeof(lightPositions) / sizeof(glm::vec3); i++) {
		Model* lightModel = new Sphere();
		lightModel->setShader(new Shader("./Shaders/vertexShaderCamera.glsl", "./Shaders/fragmentShaderSphere.glsl"));
		lightModel->createModel(sphere, sizeof(float) * 17280);

		PointLight* pointLight = new PointLight(lightPositions[i], glm::vec3(1.0f, 1.0f, 1.0f), i, lightModel);

		Transformation* transformation = new TransformationComponent();
		if (i == 2) {
			glm::vec3 ends[] = {
				glm::vec3(-15.0f, 3.0f, -20.0f),
				glm::vec3(50.0f, 3.0f, -20.0f)
			};
			pointLight->setDynamicDirection(glm::vec3(-0.02f, 0.0f, 0.0f), ends);
			transformation->addChild(new DynamicTranslate(lightPositions[i], glm::vec3(-0.02f, 0.0f, 0.0f), ends));
		}
		else {
			transformation->addChild(new Translate(lightPositions[i]));
		}
		
		transformation->addChild(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));

		lightModel->setModel(transformation);
		lightModel->setProjection(camera->getProjectionMatrix());
		lightModel->setView(camera->getViewMatrix());
		lightModel->update();
		camera->addObserver((CameraObserver*) lightModel);

		//this->addLight(pointLight);
	}

	//lights.push_back(new DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.0f, 1.0f, 0.0f), 4));

	DirectionalLight* directionalLight = new DirectionalLight(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.6f, 0.3f), 4);
	//this->addLight(directionalLight);
	//directionalLight->setDirection(glm::vec3(50.0f, 20.0f, -10.0f));
}

void SceneTwo::activate()
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void SceneTwo::deactivate()
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
} 