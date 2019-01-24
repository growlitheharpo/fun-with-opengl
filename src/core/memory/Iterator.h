#pragma once

#include <cstddef>
#include "core/utils/MemoryUtils.h"
#include "core/utils/GeneralMacroUtils.h"

namespace memory
{
	using size_t = std::size_t;

	template <typename DataType, typename s = size_t, typename d = ptrdiff_t>
	class Iterator;

	template <typename DataType, typename s = size_t, typename d = ptrdiff_t>
	class ConstIterator;

	template <typename IteratorType>
	class ReverseIterator;

	template <typename DataType, typename s, typename d>
	class Iterator
	{
	public:
		DECLARE_STANDARD_TYPEDEFS(DataType);

		typedef s size_type;
		typedef d difference_type;
		typedef Iterator<DataType, size_type, difference_type>  this_type;

		template <typename DataType, typename s, typename d>
		friend class ConstIterator;

	private:
		pointer data_ptr_;

	public:
		Iterator() : data_ptr_(nullptr) { }
		Iterator(pointer l) : data_ptr_(l) { }

		USE_DEFAULT_COPY_SEMANTICS(Iterator);
		USE_DEFAULT_MOVE_SEMANTICS(Iterator);

		~Iterator() = default;

		INLINE this_type& operator+=(difference_type offset) { data_ptr_ += offset; return *this; }
		__forceinline this_type& operator++ () { return operator+=(1); } 
		this_type operator+ (difference_type offset) const { this_type tmp(*this); return tmp.operator+=(offset); }
		this_type operator++ (int) const = delete;

		INLINE this_type& operator-=(difference_type offset) { data_ptr_ -= offset; return *this; }
		DECLARE_CANONICAL_SUBTRACTION_OPERATORS_NOPOST(this_type, difference_type)

		REF_AND_CONST_REF(operator*(), { return *data_ptr_; });
		REF_AND_CONST_REF(operator[](difference_type offset), { return operator+(offset).operator*(); });

		bool operator==(const this_type& o) const { return data_ptr_ == o.data_ptr_; }
		bool operator< (const this_type& o) const { return data_ptr_ < o.data_ptr_; }
		DECLARE_CANONICAL_COMPARISON_OPERATORS(this_type);
	};

	template <typename DataType, typename s, typename d>
	class ConstIterator
	{
	public:
		DECLARE_STANDARD_TYPEDEFS(DataType);

		typedef s size_type;
		typedef d difference_type;
		typedef ConstIterator<DataType, size_type, difference_type>  this_type;
		typedef Iterator<DataType, s, d> base_iterator;

	private:
		pointer data_ptr_;

	public:
		ConstIterator() : data_ptr_(nullptr) { }
		ConstIterator(pointer l) : data_ptr_(l) { }

		USE_DEFAULT_COPY_SEMANTICS(ConstIterator);
		USE_DEFAULT_MOVE_SEMANTICS(ConstIterator);

		ConstIterator(const base_iterator& o) noexcept : data_ptr_(o.data_ptr_) { }
		ConstIterator(base_iterator&& o) noexcept : data_ptr_(o.data_ptr_) { }

		~ConstIterator() = default;

		INLINE this_type& operator+=(difference_type offset) { data_ptr_ += offset; return *this; }
		DECLARE_CANONICAL_ADDITION_OPERATORS_NOPOST(this_type, difference_type)

		INLINE this_type& operator-=(difference_type offset) { data_ptr_ -= offset; return *this; }
		DECLARE_CANONICAL_SUBTRACTION_OPERATORS_NOPOST(this_type, difference_type)

		const_reference operator*() const { return *data_ptr_; };
		const_reference operator[](difference_type offset) const { return operator+(offset).operator*(); };

		bool operator==(const this_type& o) const { return data_ptr_ == o.data_ptr_; }
		bool operator< (const this_type& o) const { return data_ptr_ < o.data_ptr_; }
		DECLARE_CANONICAL_COMPARISON_OPERATORS(this_type);

		bool operator==(const base_iterator& o) const { return data_ptr_ == o.data_ptr_; }
		bool operator< (const base_iterator& o) const { return data_ptr_ < o.data_ptr_; }
		DECLARE_CANONICAL_COMPARISON_OPERATORS(base_iterator);
	};

	template <typename IteratorType>
	class ReverseIterator
	{
	public:
		typedef IteratorType iterator;
		USING_STANDARD_TYPEDEFS(iterator);

		using difference_type = typename iterator::difference_type;
		typedef ReverseIterator<IteratorType> this_type;

	private:
		iterator data_ptr_;

	public:
		ReverseIterator() : data_ptr_(nullptr) { }
		ReverseIterator(pointer d) : data_ptr_(d) { }

		USE_DEFAULT_COPY_SEMANTICS(ReverseIterator);
		USE_DEFAULT_MOVE_SEMANTICS(ReverseIterator);

		~ReverseIterator() = default;

		// The "trick" of reverse iterators is that their + operator calls the internal - operator, and vice-versa
		INLINE this_type& operator+=(difference_type offset) { data_ptr_ -= offset; return *this; }
		INLINE this_type& operator-=(difference_type offset) { data_ptr_ += offset; return *this; }

		DECLARE_CANONICAL_ADDITION_OPERATORS_NOPOST(this_type, difference_type)
		DECLARE_CANONICAL_SUBTRACTION_OPERATORS_NOPOST(this_type, difference_type)

		REF_AND_CONST_REF(operator*(), { return *data_ptr_; })
		REF_AND_CONST_REF(operator[](difference_type offset), { return operator+(offset).operator*(); })

		iterator base() const { return data_ptr_; }
	};
}
