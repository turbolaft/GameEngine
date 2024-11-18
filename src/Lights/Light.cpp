#include "Light.h"

Light::Light(glm::vec3 color) {
	this->color = color;
	iterator = -1;
	model = nullptr;
}

Light::Light(glm::vec3 color, int8_t iterator)
	: Light(color)
{
	this->iterator = iterator;
}

Light::Light(glm::vec3 color, int8_t iterator, Model* model)
	: Light(color, iterator)
{
	this->model = model;
}

void Light::setModel(Model* model) {
	this->model = model;
}

void Light::draw() {
	if (model != nullptr) {
		model->draw();
	}
}

glm::vec3 Light::getColor() {
	return color;
}

void Light::setColor(glm::vec3 color) {
	this->color = color;
	notifyObservers();
}

void Light::removeObserver(Model* light) {
	observers.erase(std::remove(observers.begin(), observers.end(), light), observers.end());
}