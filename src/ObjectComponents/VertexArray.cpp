#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::addBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout) {
	this->bind();
	vb->bind();
	const auto& elements = layout->getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout->getStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
	vb->unbind();
	this->unbind();
}

void VertexArray::addBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout, const IndexBuffer* index) {
	this->bind();
	vb->bind();
	index->bind();
	const auto& elements = layout->getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout->getStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
	vb->unbind();
	index->unbind();
	this->unbind();
}

void VertexArray::bind() const {
	glBindVertexArray(m_RendererID);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}