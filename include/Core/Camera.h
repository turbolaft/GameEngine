#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Shader.h"
#include "CameraObserver.h"
#include "LightObserver.h"
#include "Light.h"

#define FORWARD 0
#define BACKWARD 1
#define LEFT 2
#define RIGHT 3

class Camera
{
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void processKeyboard(int direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void processMouseScroll(float yOffset);
	void addObserver(CameraObserver* shader);
	void removeObserver(CameraObserver* shader);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void setFirstMouse(bool firstMouse);
	void setCutoff(float cutOff);
	void setOuterCutoff(float outerCutOff);
	void setLightIterator(int lightIterator);
	void addObserver(LightObserver* lightObserver);
	void setLight(bool isLight);
	bool isLightOn() { return isLight; }

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
    float zoom;
	bool firstMouse = true;
	float lastX = 1000.0f / 2.0;
	float lastY = 750.0 / 2.0;
	float cutOff;
	float outerCutOff;
	int lightIterator;
	bool isLight = false;

	std::vector<CameraObserver*> cameraObservers;
	std::vector<LightObserver*> lightObservers;

	void updateCameraVectors();
	void notifyObservers();
};

