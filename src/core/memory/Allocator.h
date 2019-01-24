#pragma once
#include <cstddef>
#include <cstdlib>
#include "core/utils/GeneralMacroUtils.h"
#include "core/utils/MemoryUtils.h"
#include "core/memory/SizeTraits.h"

namespace memory
{
	template<typename s>
	class HeapAllocation
	{
	public:
		static void* Allocate(s size)
		{
			return malloc(size);
		}

		static void* Reallocate(void* p, s size)
		{
			return realloc(p, size);
		}

		static void Deallocate(void* ptr)
		{
			free(ptr);
		}
	};

	template <typename Val, typename STraits = DefaultSizeTraits, typename Alloc = HeapAllocation<typename STraits::size_type>>
	class Allocator
	{
	public:
		DECLARE_STANDARD_TYPEDEFS(Val)

		typedef typename STraits::size_type size_type;
		typedef typename STraits::difference_type difference_type;

		constexpr Allocator() noexcept = default;
		USE_DEFAULT_COPY_SEMANTICS(Allocator);
		USE_DEFAULT_MOVE_SEMANTICS(Allocator);
		~Allocator() = default;

		void* allocate(size_type count)
		{
			return Alloc::Allocate(count * sizeof(value_type));
		}

		void* reallocate(void* ptr, size_type count)
		{
			return Alloc::Reallocate(ptr, count * sizeof(value_type));
		}

		void deallocate(void* ptr, const size_type)
		{
			Alloc::Deallocate(ptr);
		}

		size_type max_size() const noexcept
		{
			return (static_cast<size_type>(-1) / sizeof(value_type));
		}
	};
}
