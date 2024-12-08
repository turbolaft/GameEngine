#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color) : Light(color) {
	setDirection(direction);
}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color, int8_t iterator) : Light(color, iterator) {
	setDirection(direction);
}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color, int8_t iterator, Model* model) : Light(color, iterator, model) {
	setDirection(direction);
}

glm::vec3 DirectionalLight::getDirection() {
	return direction;
}

void DirectionalLight::setDirection(glm::vec3 direction) {
	this->direction = direction;

	notifyObservers();
}

void DirectionalLight::addObserver(Model* light) {
	observers.push_back(light);

	if (iterator != -1) {
		light->onLightChange(direction, color, DIRECTIONAL_LIGHT, iterator);
	}
	else {
		light->onLightChange(direction, color, DIRECTIONAL_LIGHT);
	}
}

void DirectionalLight::notifyObservers() {
	for (LightObserver* observer : observers) {
		if (iterator != -1) {
			observer->onLightChange(direction, color, DIRECTIONAL_LIGHT, iterator);
		}
		else {
			observer->onLightChange(direction, color, DIRECTIONAL_LIGHT);
		}
	}
}