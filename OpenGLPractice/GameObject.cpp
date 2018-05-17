#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Transform.h"

core::GameObject::GameObject()
{
	addComponent(new Transform());
}

core::GameObject::~GameObject()
{
	delete transform_;
	transform_ = nullptr;

	// TODO: Deleting other components
}
