#pragma once
#include "Light.h"
#include "CameraObserver.h"

class PointLight : public Light
{
public:
	PointLight(glm::vec3 position, glm::vec3 color);
	PointLight(glm::vec3 position, glm::vec3 color, int8_t iterator);
	PointLight(glm::vec3 position, glm::vec3 color, int8_t iterator, Model* model);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	void addObserver(Model* light);
	void setDynamicDirection(glm::vec3 direction, glm::vec3 ends[]);
	void dynamicMove();

protected:
	glm::vec3 dynamicDirection;
	glm::vec3 position;
	glm::vec3 ends[2];

	void notifyObservers();
};

