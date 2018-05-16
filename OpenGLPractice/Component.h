#pragma once

namespace core
{
	class GameObject;

	class Component
	{
		friend class GameObject;

	protected:
		GameObject * attached_go_;
		explicit Component(GameObject* go) : attached_go_(go) {}

	public:
		virtual ~Component() = default;

		const GameObject& GetGameObject() const { return *attached_go_; }
	};
}
