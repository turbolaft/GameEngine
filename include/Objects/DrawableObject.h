#pragma once
#include "Shader.h"
#include <glm/glm.hpp>

class DrawableObject
{
public:
	DrawableObject();
	DrawableObject(Shader);
	virtual void draw() = 0;
	void update();
	void setShader(Shader shader);
	Shader* getShader();
	void setModel(glm::mat4);
	void setView(glm::mat4);
	void setProjection(glm::mat4);
	glm::mat4 getModel();
	glm::mat4 getView();
	glm::mat4 getProjection();
protected:
	Shader* shader;
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 model;
};

