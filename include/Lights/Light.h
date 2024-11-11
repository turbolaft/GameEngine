#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"

class Light
{
public:
	void setColor(glm::vec3 color);
	glm::vec3 getColor();
	void addObserver(Shader* light);
	void removeObserver(Shader* light);

protected:
	glm::vec3 color;
	virtual void notifyObservers() = 0;
	std::vector<Shader*> observers;
};

