#include "Sphere.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Rest of the code...

Sphere::~Sphere() {
	deleteModel();
}

void Sphere::createModel(const float points[], int size) {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sphere::draw() {
	//glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, glm::vec3(1.0f, 0.5f, 0.0f));
	//std::cout << "Model: " << model[0][0] << " " << model[0][1] << " " << model[0][2] << " " << model[0][3] << std::endl;
	shader->use();
	shader->setUniform("model", model);
	glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 2880);
	glBindVertexArray(0);
}