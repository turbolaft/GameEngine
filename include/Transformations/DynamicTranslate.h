#pragma once

#include "Translate.h"

class DynamicTranslate : public Translate {
public:
	DynamicTranslate(glm::vec3 translation, glm::vec3 dynamicTranslate, glm::vec3 ends[] = nullptr) : Translate(translation) {
		this->dynamicTranslate = dynamicTranslate;
		if (ends != nullptr) {
			this->oneEnd = ends[0];
			this->secondEnd = ends[1];
			isEnded = true;
		}
		else {
			isEnded = false;
		}
		
	}
	glm::mat4 execute(glm::mat4 matrixInput) override {
		translation.x += dynamicTranslate.x;
		translation.y += dynamicTranslate.y;
		translation.z += dynamicTranslate.z;

		isDynamic = true;

		if (isEnded) {
			if (translation.x > secondEnd.x || translation.x < oneEnd.x) {
				dynamicTranslate.x *= -1;
			}
			if (translation.y > secondEnd.y || translation.y < oneEnd.y) {
				dynamicTranslate.y *= -1;
			}
			if (translation.z > secondEnd.z || translation.z < oneEnd.z) {
				dynamicTranslate.z *= -1;
			}
		}

		return glm::translate(matrixInput, translation);
	}
private:
	glm::vec3 dynamicTranslate;
	glm::vec3 oneEnd;
	glm::vec3 secondEnd;
	bool isEnded;
};