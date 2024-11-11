#include "SceneOne.h"

#include "Transformation.h"
#include "TransformationComponent.h"
#include "Translate.h"
#include "Scale.h"
#include "Rotate.h"

void SceneOne::init(GLFWwindow* window)
{
	this->window = window;

	shaders.push_back(new Shader("./Shaders/vertexShaderDefault.glsl", "./Shaders/fragmentShaderDefault.glsl"));
	shaders.push_back(new Shader("./Shaders/vertexShaderDefault.glsl", "./Shaders/fragmentShaderDefault.glsl"));
	shaders.push_back(new Shader("./Shaders/vertexShaderSphere.glsl", "./Shaders/fragmentShaderSphere.glsl"));

	models.push_back(new Triangle());
	models[0]->createModel(points, sizeof(float) * 9);
	models[0]->setShader(*shaders[0]);
	/*models.push_back(new Rectangle());
	models[1]->createModel(rectanglePoints, sizeof(float) * 12);
	models[1]->setShader(*shaders[1]);
	models.push_back(new Sphere());
	models[2]->createModel(sphere, sizeof(float) * 17280);
	models[2]->setShader(*shaders[2]);*/

	/*Transformation* transformationSphere = new TransformationComponent();
	transformationSphere->addChild(new Translate(glm::vec3(-0.1f, -0.1f, 0.0f)));
	transformationSphere->addChild(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
	transformationSphere->addChild(new Rotate(45.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
	glm::mat4 vyslednaMatice = transformationSphere->execute(glm::mat4(1.0f));
	std::cout << "Vysledna matice: " << std::endl;
	std::cout << vyslednaMatice[0][0] << " " << vyslednaMatice[0][1] << " " << vyslednaMatice[0][2] << " " << vyslednaMatice[0][3] << std::endl;
	std::cout << vyslednaMatice[1][0] << " " << vyslednaMatice[1][1] << " " << vyslednaMatice[1][2] << " " << vyslednaMatice[1][3] << std::endl;
	std::cout << vyslednaMatice[2][0] << " " << vyslednaMatice[2][1] << " " << vyslednaMatice[2][2] << " " << vyslednaMatice[2][3] << std::endl;
	std::cout << vyslednaMatice[3][0] << " " << vyslednaMatice[3][1] << " " << vyslednaMatice[3][2] << " " << vyslednaMatice[3][3] << std::endl;
	models[2]->setModel(vyslednaMatice);*/
}