#pragma once

#include "Transformation.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Scale : public Transformation
{
public:
	Scale(glm::vec3 scale) {
		this->scale = scale;
	}
	glm::mat4 execute(glm::mat4 matrixInput) override {
		return glm::scale(matrixInput, scale);
	}
private:
	glm::vec3 scale;
};