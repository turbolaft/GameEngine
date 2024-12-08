#pragma once

#include <GL/glew.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout);
	void addBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout, const IndexBuffer* index);

	void bind() const;
	void unbind() const;
private:
	unsigned int m_RendererID;
};