#include "GameObject.h"

void core::GameObject::destroy_component(Component* c)
{
	auto iter = components_.begin();
	for (; iter != components_.end(); ++iter)
	{
		if (*iter == c)
		{
			components_.erase(iter);
			break;
		}
	}
}

void core::GameObject::add_component(Component* c)
{
	components_.push_back(c);
}
