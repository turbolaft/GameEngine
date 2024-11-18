#include "Model.h"

Model::~Model() {
	deleteModel();
}

void Model::deleteModel() {
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
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