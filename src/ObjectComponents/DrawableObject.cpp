#include "DrawableObject.h"

#include "TransformationComponent.h"

DrawableObject::DrawableObject()
{
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	transformation = nullptr;
	shader = nullptr;
}

DrawableObject::DrawableObject(Shader* shader) : DrawableObject()
{
	this->setShader(shader);
}

void DrawableObject::update()
{
	this->shader->use();
	this->shader->setUniform("model", transformation == nullptr ? glm::mat4(1.0f) : transformation->execute(glm::mat4(1.0f)));
	this->shader->setUniform("view", view);
	this->shader->setUniform("projection", projection);
}

Shader* DrawableObject::getShader()
{
	return shader;
}

void DrawableObject::setShader(Shader* shader)
{
	this->shader = shader;

	// Update the shader
	this->update();
}

void DrawableObject::setModel(Transformation* transformation)
{
	if (this->transformation != nullptr)
	{
		delete this->transformation;
	}

	this->transformation = transformation;
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
	return transformation == nullptr ? glm::mat4(1.0f) : transformation->execute(glm::mat4(1.0f));
}

glm::mat4 DrawableObject::getView()
{
	return view;
}

glm::mat4 DrawableObject::getProjection()
{
	return projection;
}