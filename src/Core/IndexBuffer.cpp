#include <SPUI/Core/IndexBuffer.hpp>

SPUI::IndexBuffer::IndexBuffer() : m_count(0)
{
	glGenBuffers(1, &m_id);
}

SPUI::IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_count(count)
{
	GLCall(glGenBuffers(1, &m_id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW))
}

SPUI::IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_id));
}

void SPUI::IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void SPUI::IndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
