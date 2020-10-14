#pragma once
#ifndef DEF_SPUI_INDEXBUFFER
#define DEF_SPUI_INDEXBUFFER

#include <GL/glew.h>
#include <SPUI/Debug.hpp>


namespace SPUI
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();
		void bind() const;
		void unbind() const;

		inline unsigned int GetCount() const { return m_count; };

	private:
		unsigned int m_id;
		unsigned int m_count;
	};
}

#endif
