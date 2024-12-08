#pragma once

#include "Rotate.h"

class DynamicRotate : public Rotate {
public:
	DynamicRotate(float angle, glm::vec3 axis, float dynamicAngle) : Rotate(angle, axis) { this->dynamicAngle = dynamicAngle; }
	glm::mat4 execute(glm::mat4 matrixInput) override {
		angle += dynamicAngle;

		isDynamic = true;

		return glm::rotate(matrixInput, glm::radians(angle), axis);
	}
private:
	float dynamicAngle;
};