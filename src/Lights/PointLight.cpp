#include "PointLight.h"

void PointLight::notifyObservers() {
	for (Shader* observer : observers) {
		observer->update(position, color);
	}
}

glm::vec3 PointLight::getPosition() {
	return position;
}

void PointLight::setPosition(glm::vec3 position) {
	this->position = position;
	notifyObservers();
}

void PointLight::update(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPosition) {
	for (Shader* observer : observers) {
		observer->update(view, projection, cameraPosition);
	}
}