#pragma once
#include "IntUtilities.h"

namespace memory
{
	template <intmax_t req_size>
	struct SizeTraits
	{
		typedef typename StorageForUMaxCount<req_size>::Unsigned size_type;
		typedef typename StorageForUMaxCount<req_size>::Signed difference_type;
	};

#ifdef _WIN64
	struct DefaultSizeTraits : SizeTraits<INT64_MAX>{};
#else
	struct DefaultSizeTraits : SizeTraits<INT32_MAX> {};
#endif
}
