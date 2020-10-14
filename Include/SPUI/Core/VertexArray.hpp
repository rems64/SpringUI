#pragma once

#include <GL/glew.h>
#include <SPUI/Core/VertexBuffer.hpp>
#include <SPUI/Core/VertexBufferLayout.hpp>
#include <SPUI/Debug.hpp>

namespace SPUI {
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(const SPUI::VertexBuffer& vb, const SPUI::VertexBufferLayout& layout);

		void bind() const;
		void unbind() const;

	private:
		unsigned int m_id;
	};
}