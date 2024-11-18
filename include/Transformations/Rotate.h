#pragma once

#include "Transformation.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Rotate : public Transformation
{
public:
	Rotate(float angle, glm::vec3 axis) {
		this->angle = angle;
		this->axis = axis;
	}
	glm::mat4 execute(glm::mat4 matrixInput) override {
		return glm::rotate(matrixInput, glm::radians(angle), axis);
	}
protected:
	float angle;
	glm::vec3 axis;
};