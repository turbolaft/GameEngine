#include "Controller.h"

#include "Application.h"
#include "ModelObject.h"
#include "Translate.h"
#include "TransformationComponent.h"
#include "Scale.h"


Controller::Controller(Camera* camera)
{
	this->camera = camera;
}

Controller::~Controller()
{
}

void Controller::pressKey(GLFWwindow* window, int key)
{
	switch (key) {
		case GLFW_KEY_W:
			camera->processKeyboard(FORWARD, Application::getDeltaTime() + 0.03f);
			break;
		case GLFW_KEY_S:
			camera->processKeyboard(BACKWARD, Application::getDeltaTime() + 0.03f);
			break;
		case GLFW_KEY_A:
			camera->processKeyboard(LEFT, Application::getDeltaTime() + 0.03f);
			break;
		case GLFW_KEY_D:
			camera->processKeyboard(RIGHT, Application::getDeltaTime() + 0.03f);
			break;
	}
}

void Controller::mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	camera->mouse_callback(window, xPos, yPos);
}

void Controller::mouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		ypos = height - ypos;

		float depth;
		glReadPixels((int)xpos, (int)ypos, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

		printf("Screen coordinates: (%f, %f), Depth: %f\n", xpos, ypos, depth);

		//createModelOnClick(screenToWorldCoords((float)xpos, (float)ypos, depth, width, height));

		if (depth < 1.0f) {
			glm::vec3 worldCoords = screenToWorldCoords((float)xpos, (float)ypos, depth, width, height);
			printf("World coordinates: (%f, %f, %f)\n", worldCoords.x, worldCoords.y, worldCoords.z);
		}
	}
}

glm::vec3 Controller::screenToWorldCoords(float xpos, float ypos, float depth, int width, int height) {
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 1000.0f);

	glm::vec3 screenPos = glm::vec3(xpos, ypos, depth);
	glm::vec4 viewport = glm::vec4(0, 0, width, height);

	glm::vec3 worldCoords = glm::unProject(screenPos, view, projection, viewport);
	return worldCoords;
}

//void Controller::createModelOnClick(glm::vec3 position)
//{
//	if (scene == nullptr) {
//		return;
//	}
//
//	Shader* shaderTextureTree = new Shader("./Shaders/vertexShaderTextureDefault.glsl", "./Shaders/fragmentShaderTextureDefault.glsl");
//	ModelObject* modelObjectTree = new ModelObject("./resources/ObjModels/tree.obj", shaderTextureTree);
//
//	modelObjectTree->setCamera(camera);
//	Transformation* treeTransformation = new TransformationComponent();
//	treeTransformation->addChild(new Scale(glm::vec3(0.1f, 0.1f, 0.1f)));
//	treeTransformation->addChild(new Translate(position));
//	modelObjectTree->setTransformation(treeTransformation);
//	modelObjectTree->update();
//	Texture* textureToBeBindTree = new Texture(GL_TEXTURE_2D, "resources/ObjModels/tree.png");
//	modelObjectTree->setTexture(textureToBeBindTree);
//
//	for (auto& mesh : modelObjectTree->getMeshes()) {
//		scene->addModel(mesh);
//	}
//}

