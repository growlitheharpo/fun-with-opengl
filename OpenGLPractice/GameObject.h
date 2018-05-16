#pragma once
#include "Component.h"
#include <vector>

namespace core
{
	class GameObject
	{
	private:
		std::vector<Component*> components_;

	public:
		void add_component(Component* c);
	};
}
