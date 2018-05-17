#pragma once

namespace core
{
	class GameObject;

	class Component
	{
		friend class GameObject;

	protected:

	public:
		virtual ~Component() = default;
	};
}
