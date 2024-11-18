#pragma once

#include "Transformation.h"

#include <glm/glm.hpp>
#include <vector>

class TransformationComponent : public Transformation
{
public:
	void addChild(Transformation* child) override;
	void removeChild(Transformation* child) override;
	glm::mat4 execute(glm::mat4);
private:
	std::vector<Transformation*> children;
};