#pragma once
#include <guiddef.h>
#include "MemoryUtils.h"

namespace core
{
	class GameObject;
	typedef GUID component_guid;

	class Component
	{
	protected:
		component_guid unique_id_;

	public:
		Component();

		DISABLE_COPY_SEMANTICS(Component);
		USE_DEFAULT_MOVE_SEMANTICS(Component);

		virtual ~Component() = default;

		INLINE component_guid getGuid() const { return unique_id_; }
		INLINE const component_guid* getGuidPtr() const { return &unique_id_; }

		INLINE static bool areGuidsEqual(const Component& a, const Component& b)
		{
			return InlineIsEqualGUID(a.unique_id_, b.unique_id_);
		}
	};
}
