#include "DrawableObject.h"

DrawableObject::DrawableObject()
{
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
}

DrawableObject::DrawableObject(Shader shader) : DrawableObject()
{
	this->setShader(shader);
}

void DrawableObject::draw()
{
	shader->use();
	shader->setUniform("model", model);
	shader->setUniform("view", view);
	shader->setUniform("projection", projection);
}

void DrawableObject::update()
{
	// Update the model matrix
	this->shader->use();
	this->shader->setUniform("model", model);
	this->shader->setUniform("view", view);
	this->shader->setUniform("projection", projection);
}

Shader* DrawableObject::getShader()
{
	return shader;
}

void DrawableObject::setShader(Shader shader)
{
	this->shader = new Shader(shader);

	// Update the shader
	this->update();
}

void DrawableObject::setModel(glm::mat4 model)
{
	this->model = model;
}

void DrawableObject::setView(glm::mat4 view)
{
	this->view = view;
}

void DrawableObject::setProjection(glm::mat4 projection)
{
	this->projection = projection;
}

glm::mat4 DrawableObject::getModel()
{
	return model;
}

glm::mat4 DrawableObject::getView()
{
	return view;
}

glm::mat4 DrawableObject::getProjection()
{
	return projection;
}