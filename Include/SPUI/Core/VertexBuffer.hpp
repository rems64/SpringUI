#pragma once
#ifndef DEF_SPUI_VERTEXBUFFER
#define DEF_SPUI_VERTEXBUFFER

#include <GL/glew.h>
#include <SPUI/Debug.hpp>


namespace SPUI
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();
		void bind() const;
		void unbind() const;

	private:
		unsigned int m_id;
	};
}

#endif
