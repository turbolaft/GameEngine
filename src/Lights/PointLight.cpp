#include "PointLight.h"

#include "Transformation.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 color)
	: Light(color)
{
	this->setPosition(position);
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color, int8_t iterator)
	: Light(color, iterator)
{
	this->setPosition(position);
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color, int8_t iterator, Model* model)
	: Light(color, iterator, model)
{
	this->setPosition(position);
}

void PointLight::notifyObservers() {
	for (LightObserver* observer : observers) {
		if (iterator != -1) {
			observer->onLightChange(position, color, POINT_LIGHT, iterator);
		}
		else {
			observer->onLightChange(position, color, POINT_LIGHT);
		}
	}
}

void PointLight::addObserver(Model* light) {
	observers.push_back(light);

	if (iterator != -1) {
		light->onLightChange(position, color, POINT_LIGHT, iterator);
	}
	else {
		light->onLightChange(position, color, POINT_LIGHT);
	}
}

glm::vec3 PointLight::getPosition() {
	return position;
}

void PointLight::setPosition(glm::vec3 position) {
	this->position = position;

	notifyObservers();
}