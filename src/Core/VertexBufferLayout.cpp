#include <SPUI/Core/VertexBufferLayout.hpp>


	SPUI::VertexBufferLayout::VertexBufferLayout() : m_stride(0)
	{

	}

	SPUI::VertexBufferLayout::~VertexBufferLayout()
	{

	}

	/*
	template<typename T>
	void SPUI::VertexBufferLayout::Push(unsigned int count)
	{
		static_assert(false);
	}
	template<>
	void SPUI::VertexBufferLayout::Push<float>(unsigned int count)
	{
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += sizeof(GLfloat) * count;
	}

	template<>
	void SPUI::VertexBufferLayout::Push<unsigned int>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_TRUE });
		m_stride += sizeof(GLuint) * count;
	};

	template<>
	void SPUI::VertexBufferLayout::Push<unsigned char>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
		m_stride += sizeof(GLbyte) * count;
	};
	*/