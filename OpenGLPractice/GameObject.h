#pragma once
#include "Component.h"
#include <vector>
#include "Logging.h"

namespace core
{
	class GameObject
	{
	private:
		std::vector<Component*> components_;

	public:
		template<typename T>
		T* addComponent(T* c);
	};


	template <typename T>
	T* GameObject::addComponent(T* c)
	{
		DEBUG_IF(dynamic_cast<Component*>(c) == nullptr,
			throw std::runtime_error("Trying to add a non-component to a GameObject!"));

		components_.push_back(c);
		// TODO: Some sort of bind function inside Component?

		return c;
	}
}
