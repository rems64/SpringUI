#pragma once
#ifndef DEF_SPUI_VERTEXBUFFERLAYOUT
#define DEF_SPUI_VERTEXBUFFERLAYOUT

#include <vector>
#include <SPUI/Debug.hpp>
#include <GL/glew.h>

namespace SPUI {
	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetSizeOfType(unsigned int type)
		{
			switch (type)
			{
				case GL_FLOAT: return sizeof(GLfloat);
				case GL_UNSIGNED_INT: return sizeof(GLuint);
				case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
			}
			ASSERT(false);
			return 0;
		}
	};
	class VertexBufferLayout
	{
	public:
		VertexBufferLayout();
		~VertexBufferLayout();

		template <typename T>
		void Push(unsigned int count)
		{
			static_assert(false);
		}

		void fPush(unsigned int count)
		{
			m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
		}

		template <>
		void Push<unsigned int>(unsigned int count)
		{
			m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
		}

		template <>
		void Push<unsigned char>(unsigned int count)
		{
			m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
			m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		}

		inline const std::vector<VertexBufferElement> GetElements() const { return m_elements; };
		inline unsigned int GetStride() const { return m_stride; };

	private:
		std::vector<VertexBufferElement> m_elements;
		unsigned int m_stride;
	};
}

#endif