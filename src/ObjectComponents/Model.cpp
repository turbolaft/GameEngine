#include "Model.h"

Model::~Model() {
	deleteModel();
}

void Model::deleteModel() {
	delete vb;
	delete va;

	if (ib != nullptr) {
		delete ib;
	}
}

void Model::onLightChange(glm::vec3 position, glm::vec3 color, int8_t type) {
	shader->update(position, color);
}

void Model::onLightChange(glm::vec3 position, glm::vec3 color, int8_t type, int8_t iterator) {
	shader->update(position, color, type, iterator);
}

void Model::onCameraChange(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPosition) {
	shader->update(view, projection, cameraPosition);
}

void Model::draw(GLenum mode, int first, int count) {
	shader->use();

	if (transformation && transformation->IsDynamic()) {
		this->shader->setUniform("model", transformation == nullptr ? glm::mat4(1.0f) : transformation->execute(glm::mat4(1.0f)));
	}
	if (texture != nullptr)
		texture->bindTexture();
	va->bind();
	glDrawArrays(mode, first, count);
	va->unbind();
	if (texture != nullptr)
		texture->unbindTexture();
	shader->unuse();
}

void Model::setTexture(Texture* texture) {
	this->texture = texture;

	texture->bindToShader(shader, "textureUnitID", 0);
}

void Model::draw(GLenum mode, GLsizei count, GLenum type, const void* indices) {
	shader->use();
	if (transformation && transformation->IsDynamic()) {
		this->shader->setUniform("model", transformation == nullptr ? glm::mat4(1.0f) : transformation->execute(glm::mat4(1.0f)));
	}
	if (texture != nullptr)
		texture->bindTexture();
	va->bind();
	glDrawElements(mode, count, type, indices);
	va->unbind();
	if (texture != nullptr)
		texture->unbindTexture();
	shader->unuse();
}

void Model::setUpModel(Shader* shader, Camera* camera, Transformation* transformation, Texture* texture) {
	this->setShader(shader);
	this->setView(camera->getViewMatrix());
	this->setProjection(camera->getProjectionMatrix());
	this->setModel(transformation);
	this->setTexture(texture);
	this->update();
}