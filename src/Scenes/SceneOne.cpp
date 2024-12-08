#include "SceneOne.h"

#include "Transformation.h"
#include "TransformationComponent.h"
#include "Translate.h"
#include "Scale.h"
#include "Rotate.h"
#include "Tetrahedron.h"
#include "Texture.h"
#include "Models/tetrahedron.h"
#include "Models/Rectangle.h"

void SceneOne::init(GLFWwindow* window)
{
	this->controller = new Controller(camera);
	this->window = window;

	Shader* shaderDefault = new Shader("./Shaders/vertexShaderDefault.glsl", "./Shaders/fragmentShaderDefault.glsl");
	Shader* shaderTexture = new Shader("./Shaders/vertexShaderTextureDefault.glsl", "./Shaders/fragmentShaderTextureDefault.glsl");

	/*models.push_back(new Triangle());
	models[0]->createModel(points, sizeof(float) * 9);
	models[0]->setShader(shaders[0]);*/

	Texture* texture = new Texture(GL_TEXTURE_2D, "./resources/Textures/grass.png");
	Texture* texture2 = new Texture(GL_TEXTURE_2D, "./resources/Textures/wooden_fence.png");

	Model* model = new Tetrahedron();
	model->createModel(tetrahedron, sizeof(float) * 12 * 8);
	model->setUpModel(shaderTexture, camera, new Translate(glm::vec3(0.0f, 0.0f, 0.0f)), texture2);
	this->addModel(model);

	Model* rect = new Rectangle();
	Transformation* rectTransformation = new TransformationComponent();
	rectTransformation->addChild(new Translate(glm::vec3(0.0f, 0.5f, 0.0f)));
	rectTransformation->addChild(new Rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
	rect->createModel(rectangle, sizeof(float) * 32);
	rect->setUpModel(new Shader("./Shaders/vertexShaderTextureDefault.glsl", "./Shaders/fragmentShaderTextureDefault.glsl"),
		camera, rectTransformation, texture);
	this->addModel(rect);
}

void SceneOne::activate()
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void SceneOne::deactivate()
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}