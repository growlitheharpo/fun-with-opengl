#pragma once
#include <cstddef>
#include <cstdlib>
#include "core/utils/GeneralMacroUtils.h"
#include "core/utils/MemoryUtils.h"
#include "core/memory/SizeTraits.h"

#ifdef _USE_STD_MEM
#include <iterator>
#endif

namespace memory
{
#ifdef _USE_STD_MEM
	using namespace std;
#else

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
	class allocator
	{
	private:
		void* ptr_;

	public:
		DECLARE_STANDARD_TYPEDEFS(Val)

		typedef typename STraits::size_type size_type;
		typedef typename STraits::difference_type difference_type;

		constexpr allocator() noexcept : ptr_(nullptr) {}
		USE_DEFAULT_COPY_SEMANTICS(allocator);
		USE_DEFAULT_MOVE_SEMANTICS(allocator);
		~allocator() = default;

		void* allocate(size_type count)
		{
			ptr_ = Alloc::Allocate(count * sizeof(value_type));
			return ptr_;
		}

		void* reallocate(size_type count)
		{
			ptr_ = Alloc::Reallocate(ptr_, count * sizeof(value_type));
			return ptr_;
		}

		void deallocate(const size_type)
		{
			Alloc::Deallocate(ptr_);
			ptr_ = nullptr;
		}

		size_type max_size() const noexcept
		{
			return (static_cast<size_type>(-1) / sizeof(value_type));
		}

		MUT_AND_CONST_OF_TYPE(void*, void const*, get_data(), { return ptr_; })
	};
#endif
}
