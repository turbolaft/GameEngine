#include "Camera.h"
#include "Skybox.h"
#include "Mesh.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: position(position), worldUp(up), yaw(yaw), pitch(pitch), movementSpeed(2.5f), mouseSensitivity(0.03f), zoom(45.0f)
{
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + front, up);
	//return glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), up);
	//return glm::lookAt(position, front, up);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(zoom), 1000.0f / 750.0f, 0.1f, 100.0f);
}

void Camera::processKeyboard(int direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT) {
		position -= right * velocity;
		updateCameraVectors();
	}
	if (direction == RIGHT) {
		position += right * velocity;
		updateCameraVectors();
	}

	notifyObservers();
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (constrainPitch) {
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f; 
	}

	updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset) {
	zoom -= yOffset;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;

	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	// pitch - around x
	// yaw - around y
	// roll - around z
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));

	/*printf("Camera position: %f %f %f\n", position.x, position.y, position.z);
	printf("Camera up: %f %f %f\n", up.x, up.y, up.z);
	printf("Camera pitch: %f\n", pitch);
	printf("Camera yaw: %f\n", yaw);*/

	notifyObservers();
}

void Camera::addObserver(CameraObserver* shader)
{
	cameraObservers.push_back(shader);
}

void Camera::removeObserver(CameraObserver* shader)
{
	cameraObservers.erase(std::remove(cameraObservers.begin(), cameraObservers.end(), shader), cameraObservers.end());
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float) xpos;
		lastY = (float) ypos;
		firstMouse = false;
	}

	float xoffset = (float) xpos - lastX;
	float yoffset = lastY - (float) ypos;

	lastX = (float) xpos;
	lastY = (float) ypos;

	this->processMouseMovement(xoffset, yoffset);
}

void Camera::setFirstMouse(bool firstMouse)
{
	this->firstMouse = firstMouse;
}

void Camera::setCutoff(float cutOff)
{
	this->cutOff = cutOff;
}

void Camera::setOuterCutoff(float outerCutOff)
{
	this->outerCutOff = outerCutOff;
}

void Camera::setLightIterator(int lightIterator)
{
	this->lightIterator = lightIterator;
}

void Camera::addObserver(LightObserver* lightObserver)
{
	lightObservers.push_back(lightObserver);

	if (lightIterator != -1) {
		lightObserver->onLightChange(position, front, SPOT_LIGHT, cutOff, outerCutOff, lightIterator);
	}
	else {
		lightObserver->onLightChange(position, front, SPOT_LIGHT, cutOff, outerCutOff);
	}
}

void Camera::notifyObservers() {
	for (auto observer : cameraObservers)
	{
		if (Skybox* skybox = dynamic_cast<Skybox*>(observer)) {
			if (skybox->getSkybox()) {

				observer->onCameraChange(glm::mat4(glm::mat3(getViewMatrix())), getProjectionMatrix(), position);

				continue;
			}
		}

		if (Mesh* mesh = dynamic_cast<Mesh*>(observer)) {
			if (mesh->getSkybox()) {

				observer->onCameraChange(glm::mat4(glm::mat3(getViewMatrix())), getProjectionMatrix(), position);

				continue;
			}
		}

		observer->onCameraChange(getViewMatrix(), getProjectionMatrix(), position);
	}

	if (isLight) {
		
		for (auto observer : lightObservers)
		{
			if (lightIterator != -1) {
				observer->onLightChange(position, front, SPOT_LIGHT, cutOff, outerCutOff, lightIterator);
			}
			else {
				observer->onLightChange(position, front, SPOT_LIGHT, cutOff, outerCutOff);
			}
		}

	}
}

void Camera::setLight(bool isLight)
{
	this->isLight = isLight;
}