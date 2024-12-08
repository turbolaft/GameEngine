#include "Triangle.h"

#include <iostream>

void Triangle::createModel(const float points[], int size) {
	vb = new VertexBuffer(points, size);
	VertexBufferLayout* layout = new VertexBufferLayout();
	layout->push<float>(3);
	va = new VertexArray();
	va->addBuffer(vb, layout);
}

void Triangle::draw() {
	Model::draw(GL_TRIANGLES, 0, 3);
}