#include "Light.h"

glm::vec3 Light::getColor() {
	return color;
}

void Light::setColor(glm::vec3 color) {
	this->color = color;
	notifyObservers();
}

void Light::addObserver(Shader* light) {
	observers.push_back(light);
}

void Light::removeObserver(Shader* light) {
	observers.erase(std::remove(observers.begin(), observers.end(), light), observers.end());
}