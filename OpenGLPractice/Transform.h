#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace core
{
	class Transform : public Component
	{
	private:
	public:
		glm::mat4x4 transform;
	};
}
