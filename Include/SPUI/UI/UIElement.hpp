#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SPUI
{
	class UIElement
	{
	public:
		UIElement();
		~UIElement();

	private:
		glm::vec2 m_position;
		glm::vec2 m_size;
		float rotation;
	};
}