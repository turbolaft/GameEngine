#pragma once

class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int size);
	~IndexBuffer();

	void bind() const;
	void unbind() const;
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};