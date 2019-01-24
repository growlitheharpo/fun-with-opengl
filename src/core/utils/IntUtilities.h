#pragma once
#include <cstdint>

typedef uint8_t byte_t;

template<intmax_t value>
struct BitcountSigned
{
	static const byte_t count = 1 + BitcountSigned<value / 2>::count;
};

template<uintmax_t value>
struct BitcountUnsigned
{
	static const byte_t count = 1 + BitcountUnsigned<value / 2>::count;
};

template<> struct BitcountSigned<0> { static const byte_t count = 0; };
template<> struct BitcountUnsigned<0> { static const byte_t count = 0; };

template<byte_t N1> struct TypeSelector {};
template<> struct TypeSelector<0> { typedef uint8_t Unsigned; typedef int8_t Signed; };
template<> struct TypeSelector<1> { typedef uint16_t Unsigned; typedef int16_t Signed; };
template<> struct TypeSelector<2> { typedef uint32_t Unsigned; typedef int32_t Signed; };
template<> struct TypeSelector<3> { typedef uint64_t Unsigned; typedef int64_t Signed; };

template<typename T> struct StorageForBitcount
{
	enum { N = T::count};
	enum { unsigned_value = N > 64 ? -1 : N > 32 ? 3 : N > 16 ? 2 : N > 8 ? 1 : 0 };
	typedef typename TypeSelector<unsigned_value>::Unsigned Unsigned;

	enum { signed_value = N > 63 ? -1 : N > 31 ? 3 : N > 15 ? 2 : N > 7 ? 1 : 0 };
	typedef typename TypeSelector<signed_value>::Signed Signed;
};

template <intmax_t value> struct StorageForMaxCount
{
	typedef typename StorageForBitcount<BitcountSigned<value>>::Unsigned Unsigned;
	typedef typename StorageForBitcount<BitcountSigned<value>>::Signed Signed;
};

template <intmax_t value> struct StorageForUMaxCount
{
	typedef typename StorageForBitcount<BitcountUnsigned<value>>::Unsigned Unsigned;
	typedef typename StorageForBitcount<BitcountUnsigned<value>>::Signed Signed;
};
