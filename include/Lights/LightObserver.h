#pragma once

class LightObserver
{
public:
	virtual void onLightChange(glm::vec3 position, glm::vec3 color, int8_t type) = 0;
	virtual void onLightChange(glm::vec3 position, glm::vec3 color, int8_t type, int8_t iterator) = 0;
	virtual void onLightChange(glm::vec3 position, glm::vec3 direction, int8_t type, float cutOff, float outerCutOff) = 0;
	virtual void onLightChange(glm::vec3 position, glm::vec3 direction, int8_t type, float cutOff, float outerCutOff, int8_t iterator) = 0;
};