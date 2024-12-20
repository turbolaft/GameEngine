#include "Tree.h"

#include <glm/gtc/matrix_transform.hpp>

void Tree::createModel(const float points[], int size) {
	vb = new VertexBuffer(points, size);
	VertexBufferLayout* layout = new VertexBufferLayout();
	layout->push<float>(3);
	layout->push<float>(3);
	va = new VertexArray();
	va->addBuffer(vb, layout);
}

void Tree::draw() {
	Model::draw(GL_TRIANGLES, 0, 92814);
}