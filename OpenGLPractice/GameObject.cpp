#include "GameObject.h"
#include "Transform.h"

core::GameObject::GameObject()
{
	transform_ = addComponent(new Transform());
}

core::GameObject::~GameObject()
{
	delete transform_;
	transform_ = nullptr;

	// TODO: Deleting other components
}
