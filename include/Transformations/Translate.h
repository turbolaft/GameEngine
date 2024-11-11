#pragma once
#include "Transformation.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Translate : public Transformation
{
public:
	Translate(glm::vec3 translation) {
		this->translation = translation;
	}
	glm::mat4 execute(glm::mat4 matrixInput) override {
		return glm::translate(matrixInput, translation);
	}
private:
	glm::vec3 translation;
};