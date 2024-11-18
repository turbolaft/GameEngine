#include "SceneOne.h"

#include "Transformation.h"
#include "TransformationComponent.h"
#include "Translate.h"
#include "Scale.h"
#include "Rotate.h"

void SceneOne::init(GLFWwindow* window)
{
	this->controller = new Controller(camera);
	this->window = window;

	shaders.push_back(new Shader("./Shaders/vertexShaderDefault.glsl", "./Shaders/fragmentShaderDefault.glsl"));
	shaders.push_back(new Shader("./Shaders/vertexShaderDefault.glsl", "./Shaders/fragmentShaderDefault.glsl"));
	shaders.push_back(new Shader("./Shaders/vertexShaderSphere.glsl", "./Shaders/fragmentShaderSphere.glsl"));

	models.push_back(new Triangle());
	models[0]->createModel(points, sizeof(float) * 9);
	models[0]->setShader(shaders[0]);
}