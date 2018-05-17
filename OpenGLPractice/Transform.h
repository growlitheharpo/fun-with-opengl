#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace core
{
	class Transform : public Component
	{
	private:
	public:
		Transform();

		glm::mat4 transform;
	};
}
