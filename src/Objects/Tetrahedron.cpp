#include "Tetrahedron.h"

void Tetrahedron::createModel(const float points[], int size)
{
	vb = new VertexBuffer(points, size);
	VertexBufferLayout* layout = new VertexBufferLayout();
	layout->push<float>(3);
	layout->push<float>(3);
	layout->push<float>(2);
	va = new VertexArray();
	va->addBuffer(vb, layout);
}

void Tetrahedron::draw()
{
	Model::draw(GL_TRIANGLES, 0, 12);
}