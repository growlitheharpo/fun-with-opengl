#include "GameObject.h"


void core::GameObject::add_component(Component* c)
{
	components_.push_back(c);
}
