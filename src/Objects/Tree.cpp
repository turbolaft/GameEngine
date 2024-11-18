#include "Tree.h"

#include <glm/gtc/matrix_transform.hpp>

void Tree::createModel(const float points[], int size) {
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
}

void Tree::draw() {

	shader->use();
	if (transformation && transformation->IsDynamic()) {
		this->shader->setUniform("model", transformation == nullptr ? glm::mat4(1.0f) : transformation->execute(glm::mat4(1.0f)));
	}

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 92814);
	glBindVertexArray(0);
}