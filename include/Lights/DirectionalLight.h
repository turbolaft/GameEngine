#pragma once
#include "Light.h"

#include "LightObserver.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(glm::vec3 direction, glm::vec3 color);
	DirectionalLight(glm::vec3 direction, glm::vec3 color, int8_t iterator);
	DirectionalLight(glm::vec3 direction, glm::vec3 color, int8_t iterator, Model* model);
	glm::vec3 getDirection();
	void setDirection(glm::vec3 direction);
	void addObserver(Model* light);

protected:
	glm::vec3 direction;

	void notifyObservers();
};