#include "SceneFour.h"

#include "Skybox.h"
#include "ModelObject.h"
#include "Models/skycube.h"
#include "Translate.h"

void SceneFour::init(GLFWwindow* window)
{
	Shader* shader = new Shader("./Shaders/vertexShaderCubemap.glsl", "./Shaders/fragmentShaderCubemap.glsl");
	this->controller = new Controller(camera);
	this->window = window;

	Shader* shaderTextureHouse = new Shader("./Shaders/vertexShaderTextureDefault.glsl", "./Shaders/fragmentShaderTextureDefault.glsl");
	ModelObject* modelObjectHouse = new ModelObject("./resources/ObjModels/skydome.obj", shaderTextureHouse, true);

	modelObjectHouse->setCamera(camera);
	modelObjectHouse->setTransformation(new Translate(glm::vec3(0.0f, 0.0f, 0.0f)));
	Texture* textureToBeBindHouse = new Texture(GL_TEXTURE_2D, "resources/ObjModels/skydome.png");
	modelObjectHouse->setTexture(textureToBeBindHouse);

	for (auto& mesh : modelObjectHouse->getMeshes()) {
		this->addModel(mesh);
	}

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
	skybox->setView(glm::mat4(glm::mat3(camera->getViewMatrix())));
	skybox->update();
	addModel(skybox);

	Shader* shaderTexture = new Shader("./Shaders/vertexShaderTextureDefault.glsl", "./Shaders/fragmentShaderTextureDefault.glsl");
	ModelObject* modelObject = new ModelObject("./resources/ObjModels/zombie.obj", shaderTexture);

	modelObject->setCamera(camera);
	modelObject->setTransformation(new Translate(glm::vec3(0.0f, 0.0f, 0.0f)));
	Texture* textureToBeBind = new Texture(GL_TEXTURE_2D, "resources/ObjModels/zombie.png");
	modelObject->setTexture(textureToBeBind);

	for (auto& mesh : modelObject->getMeshes()) {
		this->addModel(mesh);
	}
}

void SceneFour::activate()
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void SceneFour::deactivate()
{
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}