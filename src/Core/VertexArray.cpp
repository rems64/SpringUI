#include <SPUI/Core/VertexArray.hpp>

	SPUI::VertexArray::VertexArray()
	{
		GLCall(glCreateVertexArrays(1, &m_id));
	}

	SPUI::VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_id));
	}

	void SPUI::VertexArray::addBuffer(const SPUI::VertexBuffer& vb, const SPUI::VertexBufferLayout& layout)
	{
		bind();
		vb.bind();
		const auto& elements = layout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		}
	}

	void SPUI::VertexArray::bind() const
	{
		GLCall(glBindVertexArray(m_id));
	}

	void SPUI::VertexArray::unbind() const
	{
		GLCall(glBindVertexArray(0));
	}
