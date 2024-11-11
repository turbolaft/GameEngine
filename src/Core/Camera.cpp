#include "Camera.h"

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
	return glm::perspective(glm::radians(zoom), 800.0f / 600.0f, 0.1f, 100.0f);
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
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));

	notifyObservers();
}

void Camera::addObserver(CameraObserver* shader)
{
	observers.push_back(shader);
}

void Camera::notifyObservers()
{
	for (auto observer : observers)
	{
		observer->update(getViewMatrix(), getProjectionMatrix(), position);
	}
}

void Camera::removeObserver(CameraObserver* shader)
{
	observers.erase(std::remove(observers.begin(), observers.end(), shader), observers.end());
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; 

	lastX = xpos;
	lastY = ypos;

	this->processMouseMovement(xoffset, yoffset);
}