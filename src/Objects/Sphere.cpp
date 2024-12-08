#include "Sphere.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

// Rest of the code...

Sphere::~Sphere() {
	deleteModel();
}

void Sphere::createModel(const float points[], int size) {
	vb = new VertexBuffer(points, size);
	VertexBufferLayout* layout = new VertexBufferLayout;
	layout->push<float>(3);
	layout->push<float>(3);
	va = new VertexArray;
	va->addBuffer(vb, layout);
}

void Sphere::draw() {
	Model::draw(GL_TRIANGLES, 0, 2880);
}