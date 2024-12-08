#include "Rectangle.h"

Rectangle::~Rectangle() {
	Model::~Model();
}

void Rectangle::createModel(const float points[], int size) {

	vb = new VertexBuffer(points, size);
	ib = new IndexBuffer(indices, 6);
	VertexBufferLayout* layout = new VertexBufferLayout();
	layout->push<float>(3);
	layout->push<float>(3);
	layout->push<float>(2);
	va = new VertexArray();
	va->addBuffer(vb, layout, ib);
}

void Rectangle::draw() {
	Model::draw(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
}