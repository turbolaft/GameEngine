#pragma once
#include <glm/glm.hpp>

class CameraObserver
{
public:
	virtual void onCameraChange(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPosition) = 0;
};