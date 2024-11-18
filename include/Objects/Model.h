#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "DrawableObject.h"
#include "CameraObserver.h"
#include "LightObserver.h"

class Model : public DrawableObject, public CameraObserver, public LightObserver
{
public:
	virtual ~Model();
	virtual void createModel(const float points[], int size) = 0;
	virtual void deleteModel();
	void onLightChange(glm::vec3 position, glm::vec3 color, int8_t type);
	void onLightChange(glm::vec3 position, glm::vec3 color, int8_t type, int8_t iterator);
	void onCameraChange(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPosition);
protected:
	GLuint VBO, VAO;
};

