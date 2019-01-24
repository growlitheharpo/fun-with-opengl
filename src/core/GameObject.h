#pragma once
#include <vector> // TODO: Replace with DynamicVector
#include "core/Component.h"
#include "core/Logging.h"

namespace core
{
	class Transform;

	class GameObject
	{
	private:
		std::vector<Component*> components_;
		Transform* transform_;

	public:
		GameObject();
		~GameObject();

		template<typename T>
		T* addComponent(T* c);

		Transform const& transform() const { return *transform_; }
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
