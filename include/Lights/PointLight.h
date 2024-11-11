#pragma once
#include "Light.h"
#include "CameraObserver.h"

class PointLight : public Light, public CameraObserver
{
public:
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	void update(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPosition) override;

protected:
	glm::vec3 position;
	virtual void notifyObservers();
};

