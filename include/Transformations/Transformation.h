#pragma once
#include <glm/glm.hpp>

class Transformation
{
public:
	virtual glm::mat4 execute(glm::mat4) = 0;
	virtual void addChild(Transformation* child) { }
	virtual void removeChild(Transformation* child) { }
	bool IsDynamic() const { return isDynamic; }

protected:
	bool isDynamic = false;
};

