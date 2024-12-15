#include "PointLight.h"

#include "Transformation.h"
#include "Translate.h"

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

void PointLight::addObserver(Model* light) {
	observers.push_back(light);

	if (iterator != -1) {
		light->onLightChange(position, color, POINT_LIGHT, iterator);
	}
	else {
		light->onLightChange(position, color, POINT_LIGHT);
	}
}

void PointLight::setDynamicDirection(glm::vec3 direction, glm::vec3 ends[]) {
	this->dynamicDirection = direction;
	this->ends[0] = ends[0];
	this->ends[1] = ends[1];
}

void PointLight::dynamicMove() {
	if (dynamicDirection != glm::vec3(0.0f)) {
		position += dynamicDirection;

		if (position.x > ends[1].x || position.x < ends[0].x) {
			dynamicDirection.x *= -1;
		}
		if (position.y > ends[1].x || position.y < ends[0].y) {
			dynamicDirection.y *= -1;
		}
		if (position.z > ends[1].x || position.z < ends[0].z) {
			dynamicDirection.z *= -1;
		}

		notifyObservers();
	}
}

glm::vec3 PointLight::getPosition() {
	return position;
}

void PointLight::setPosition(glm::vec3 position) {
	this->position = position;

	notifyObservers();
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