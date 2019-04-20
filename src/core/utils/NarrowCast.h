#pragma once

#include "core/utils/Assert.h"

template <typename TDst, typename TSrc>
TDst narrow_cast(TSrc v)
{
	TDst r = static_cast<TDst>(v);

	ASSERT(r == v);
	ASSERT((TSrc)r == v);
	ASSERT(r == (TDst)v);

	return r;
}
