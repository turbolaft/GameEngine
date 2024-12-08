#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"
#include "LightObserver.h"
#include "Model.h"

#define POINT_LIGHT 1
#define DIRECTIONAL_LIGHT 2
#define SPOT_LIGHT 3

class Light
{
public:
	Light(glm::vec3 color);
	Light(glm::vec3 color, int8_t iterator);
	Light(glm::vec3 color, int8_t iterator, Model* model);
	void setColor(glm::vec3 color);
	glm::vec3 getColor();
	virtual void addObserver(Model* light) = 0;
	void removeObserver(Model* light);
	void setModel(Model* model);
	virtual void draw();


protected:
	glm::vec3 color;
	virtual void notifyObservers() = 0;
	std::vector<LightObserver*> observers;
	int8_t iterator;
	Model* model;
};

