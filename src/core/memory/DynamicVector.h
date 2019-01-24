#pragma once
#include <cstdlib>
#include <limits>

#include "core/memory/Iterator.h"
#include "core/memory/Allocator.h"
#include "core/Logging.h"

namespace memory
{
	template <typename DataType, typename AllocT = Allocator<DataType>, typename AllocT::size_type initial_alloc = 5>
	class DynamicVector
	{
	public:
		DECLARE_STANDARD_TYPEDEFS(DataType)

		typedef AllocT alloc;
		typedef typename alloc::size_type size_type;
		typedef typename alloc::difference_type difference_type;

		typedef Iterator<value_type, size_type, difference_type> iterator;
		typedef ConstIterator<value_type, size_type, difference_type> const_iterator;
		typedef ReverseIterator<iterator> reverse_iterator;
		typedef ReverseIterator<const_iterator> const_reverse_iterator;

		typedef DynamicVector this_type;

	private:
		enum iterator_check_type
		{
			disallow_special_cases = 0,
			allow_begin_when_zero = FLAG(0),
			allow_end = FLAG(1),
		};

		static const size_type GROWTH_RATE = 2;

		alloc allocator;
		size_type capacity_, size_;
		void* internal_buffer_;

		void* reallocate(size_type new_capacity);

		INLINE bool is_iterator_valid(const_iterator iter, iterator_check_type allow_flags);
		INLINE void check_iterator_valid(const_iterator iter, iterator_check_type allow_flags);
		INLINE pointer push_back_get_location_internal();
		INLINE pointer insert_get_location_internal(const_iterator position);

	public:
		DynamicVector() : capacity_(0), size_(0), internal_buffer_(nullptr) { }
		explicit DynamicVector(size_type initial_capacity);

		DISABLE_COPY_SEMANTICS(DynamicVector);
		USE_DEFAULT_MOVE_SEMANTICS(DynamicVector);

		~DynamicVector();


		// **** ITERATORS **** */
		MUT_AND_CONST_OF_TYPE(iterator, const_iterator, begin(), { return { reinterpret_cast<pointer>(internal_buffer_) }; });
		MUT_AND_CONST_OF_TYPE(iterator, const_iterator, end(), { return { reinterpret_cast<pointer>(internal_buffer_) + size_ }; });
		MUT_AND_CONST_OF_TYPE(reverse_iterator, const_reverse_iterator, rbegin(), { return { reinterpret_cast<pointer>(internal_buffer_) + size_ }; });
		MUT_AND_CONST_OF_TYPE(reverse_iterator, const_reverse_iterator, rend(), { return { reinterpret_cast<pointer>(internal_buffer_) }; });
		const_iterator cbegin() const { return begin(); }
		const_iterator cend() const { return end(); }
		const_reverse_iterator crbegin() const { return rbegin(); }
		const_reverse_iterator crend() const { return rend(); }


		// **** CAPACITY **** */
		INLINE size_type size()		const { return size_; }
		INLINE size_type max_size() const { return std::numeric_limits<size_type>::max(); }
		INLINE size_type capacity() const { return capacity_; }
		INLINE bool empty()			const { return size_ == 0; }
		void resize(size_type count);
		void resize(size_type count, const_reference val);
		void reserve(size_type count);


		// **** ELEMENT ACCESS **** */
		MUT_AND_CONST_OF_TYPE(reference, const_reference, 
			operator[](size_type index), { return reinterpret_cast<pointer>(internal_buffer_)[index]; });
		MUT_AND_CONST_OF_TYPE(reference, const_reference, 
			at(size_type index), { return operator[](index); });
		MUT_AND_CONST_OF_TYPE(reference, const_reference, 
			front(), { DEBUG_IF(size_ == 0, throw std::out_of_range("")); return operator[](0); });
		MUT_AND_CONST_OF_TYPE(reference, const_reference, 
			back(), { DEBUG_IF(size_ == 0, throw std::out_of_range("")); return operator[](size_ - 1); });

		pointer data() { return reinterpret_cast<pointer>(internal_buffer_); };
		const_pointer data() const { return reinterpret_cast<const_pointer>(internal_buffer_); }


		// **** MODIFIERS **** */
		void push_back();
		void push_back(const_reference other);
		void push_back(value_type&& other);
		void* push_back_for_placement_new();
		void pop_back();
		void insert(const_iterator position);
		void insert(const_iterator position, const_reference val);
		void insert(const_iterator position, value_type&& val);
		void* insert_for_placement_new(iterator position);
		void erase(iterator position);
		void erase(iterator first, iterator last);
		void swap(this_type& other) noexcept;
		void clear();

		template<typename... Ts>
		void emplace_back(Ts&&... args);

		template<typename... Ts>
		void emplace(const_iterator position, Ts&&... args);
	};

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	bool DynamicVector<DataType, AllocT, initial_alloc>::
		is_iterator_valid(const_iterator iter, iterator_check_type allow_flags)
	{
		if (size() == 0)
		{
			return (allow_flags & allow_begin_when_zero) && iter == begin();
		}

		if (iter < begin())
			return false;

		if (iter > end())
			return false;

		return iter != end() || (allow_flags & allow_end);
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		check_iterator_valid(const_iterator iter, iterator_check_type allow_flags)
	{
		if (!is_iterator_valid(iter, allow_flags))
			throw std::out_of_range("");
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void* DynamicVector<DataType, AllocT, initial_alloc>::
		reallocate(size_type new_capacity)
	{
		size_type original_capacity = capacity_;
		void* original_ptr = internal_buffer_;

		capacity_ = new_capacity;
		internal_buffer_ = allocator.reallocate(original_ptr, capacity_);

		return reinterpret_cast<void*>(
			reinterpret_cast<pointer>(internal_buffer_) + original_capacity);
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	typename DynamicVector<DataType, AllocT, initial_alloc>::pointer DynamicVector<DataType, AllocT, initial_alloc>::
		push_back_get_location_internal()
	{
		pointer new_location;

		if (capacity() == 0)
			new_location = reinterpret_cast<pointer>(reallocate(initial_alloc));
		else if (size() == capacity())
			new_location = reinterpret_cast<pointer>(reallocate(static_cast<size_type>(GROWTH_RATE * capacity())));
		else
			new_location = reinterpret_cast<pointer>(internal_buffer_) + size_;

		++size_;
		return new_location;
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	typename DynamicVector<DataType, AllocT, initial_alloc>::pointer DynamicVector<DataType, AllocT, initial_alloc>::
		insert_get_location_internal(const_iterator position)
	{
		DEBUG_STATEMENT(check_iterator_valid(position, iterator_check_type(allow_begin_when_zero | allow_end)););

		if (position == end() || size() == 0)
		{
			return push_back_get_location_internal();
		}

		// Allocate a new element
		push_back_for_placement_new();

		// Copy everything forward 1 element using its move constructor (hopefully)
		difference_type i = 0;
		reverse_iterator iter = rbegin();
		for (; const_iterator(iter.base()) != position; ++iter, ++i)
		{
			*iter = std::move(*(iter + 1));
		}

		return &(*iter);
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	DynamicVector<DataType, AllocT, initial_alloc>::DynamicVector(size_type initial_capacity) : capacity_(0), size_(0), internal_buffer_(nullptr)
	{
		reserve(initial_capacity);
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	DynamicVector<DataType, AllocT, initial_alloc>::~DynamicVector()
	{
		this->clear();
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		resize(size_type count)
	{
		DEBUG_STATEMENT(
			{
				if (count == size_)
					return;
			});

		if (count > size_)
		{
			reallocate(count);
			while (size_ < capacity_)
				push_back(value_type());
		}
		else if (count < size_)
		{
			reserve(count);
		}
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		resize(size_type count, const_reference val)
	{
		DEBUG_STATEMENT(
			{
				if (count == size_)
					return;
			});

		if (count > size_)
		{
			reallocate(count);
			while (size_ < capacity_)
				push_back(val);
		}
		else if (count < size_)
		{
			reserve(count);
		}
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		reserve(size_type count)
	{
		DEBUG_STATEMENT(
			{
				if (count == capacity_)
				{
					LOG_ERR("Reserving a vector to the size it already is!");
					return;
				}
			});

		if (count > size_)
		{
			reallocate(count);
		}
		else if (count < size_)
		{
			for (iterator iter = end() - 1; iter != (begin() + count); --iter)
			{
				(*iter).~value_type();
			}
			reallocate(count);
		}
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::push_back()
	{
		pointer new_location = push_back_get_location_internal();
		new (new_location)value_type();
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		push_back(const_reference other)
	{
		pointer new_location = push_back_get_location_internal();
		new (new_location)value_type(other);
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::push_back(value_type&& other)
	{
		pointer new_location = push_back_get_location_internal();
		new (new_location)value_type(std::forward<value_type>(other));
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void* DynamicVector<DataType, AllocT, initial_alloc>::
		push_back_for_placement_new()
	{
		return static_cast<void*>(push_back_get_location_internal());
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		pop_back()
	{
		pointer final_element = &back();
		final_element->~value_type();
		--size_;

		DEBUG_STATEMENT(
			{
				memset(final_element, 0, sizeof(value_type));
				final_element = nullptr;
			});
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		insert(const_iterator position)
	{
		pointer position_ptr = insert_get_location_internal(position);
		new (position_ptr)value_type();
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		insert(const_iterator position, const_reference val)
	{
		pointer position_ptr = insert_get_location_internal(position);
		new (position_ptr)value_type(val);
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		insert(const_iterator position, value_type&& val)
	{
		pointer position_ptr = insert_get_location_internal(position);
		new (position_ptr)value_type(val);
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void* DynamicVector<DataType, AllocT, initial_alloc>::
		insert_for_placement_new(iterator position)
	{
		return static_cast<void*>(insert_get_location_internal(position));
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		erase(iterator position)
	{
		DEBUG_STATEMENT(check_iterator_valid(position, disallow_special_cases););
		erase(position, position);
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		erase(iterator first, iterator last)
	{
		DEBUG_STATEMENT(check_iterator_valid(first, disallow_special_cases););
		DEBUG_STATEMENT(check_iterator_valid(last, disallow_special_cases););

		// Destruct objects
		size_type destroyed_count = 0;
		iterator destruct_iter = first;
		while (destruct_iter <= last)
		{
			(*destruct_iter).~value_type();
			++destruct_iter;
			++destroyed_count;
		}

		// now, destruct_iter == last + 1, so let's move everything back
		while (destruct_iter != end())
		{
			(*first) = std::move((*destruct_iter));
			++first;
			++destruct_iter;
		}

		size_ -= destroyed_count;
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		swap(this_type& other) noexcept
	{
		std::swap(this->size_, other.size);
		std::swap(this->capacity_, other.capacity_);
		std::swap(this->internal_buffer_, other.internal_buffer_);
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		clear()
	{
		for (auto& iter : *this)
			iter.~value_type();

		allocator.deallocate(internal_buffer_, capacity_);
		memset(this, 0, sizeof this);
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	template <typename ... Ts>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		emplace_back(Ts&&... args)
	{
		pointer new_location = push_back_get_location_internal();
		new (new_location)value_type(std::forward<Ts>(args)...);
	}

	template <typename DataType, typename AllocT, typename AllocT::size_type initial_alloc>
	template <typename ... Ts>
	void DynamicVector<DataType, AllocT, initial_alloc>::
		emplace(const_iterator position, Ts&&... args)
	{
		pointer new_location = insert_get_location_internal(position);
		new (new_location)value_type(std::forward<Ts>(args)...);
	}
}
