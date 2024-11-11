#include "Model.h"

Model::~Model() {
	deleteModel();
}

void Model::deleteModel() {
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}