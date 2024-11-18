#pragma once

#include "Rotate.h"

class DynamicRotate : public Rotate {
public:
	DynamicRotate(float angle, glm::vec3 axis) : Rotate(angle, axis) {}
	glm::mat4 execute(glm::mat4 matrixInput) override {
		angle += 0.8f;

		isDynamic = true;

		return glm::rotate(matrixInput, glm::radians(angle), axis);
	}
};