#pragma once

#define DECLARE_CANONICAL_COMPARISON_OPERATORS(name_of_type)                                                      \
		INLINE bool operator!= (const name_of_type& o) const { return !operator==(o); }                           \
		INLINE bool operator<= (const name_of_type& o) const { return operator<(o) || operator==(o); }            \
		INLINE bool operator>  (const name_of_type& o) const { return !operator<(o) && !operator==(o); }          \
		INLINE bool operator>= (const name_of_type& o) const { return !operator<(o); }

#define DECLARE_CANONICAL_COMPARISON_OPERATORS_BY_VALUE(name_of_type)                                             \
		INLINE bool operator!= (name_of_type o) const { return !operator==(o); }                           \
		INLINE bool operator<= (name_of_type o) const { return operator<(o) || operator==(o); }            \
		INLINE bool operator>  (name_of_type o) const { return !operator<(o) && !operator==(o); }          \
		INLINE bool operator>= (name_of_type o) const { return !operator<(o); }

#define DECLARE_STANDARD_TYPEDEFS(input_type)          \
        typedef	      input_type      value_type;      \
        typedef	      input_type*     pointer;         \
        typedef const input_type*     const_pointer;   \
        typedef       input_type&     reference;       \
        typedef const input_type&     const_reference; \

#define USING_STANDARD_TYPEDEFS(input_type)                            \
        using value_type = typename input_type::value_type;            \
        using pointer = typename input_type::pointer;                  \
        using const_pointer = typename input_type::const_pointer;      \
        using reference = typename input_type::reference;              \
        using const_reference = typename input_type::const_reference;  \

#define REF_AND_CONST_REF(func_signature, implementation)       \
        reference func_signature implementation                 \
        const_reference func_signature const implementation

#define MUT_AND_CONST_OF_TYPE(type, const_type, func_signature, implementation) \
        type func_signature implementation                                      \
        const_type func_signature const implementation

#define DECLARE_CANONICAL_ADDITION_OPERATORS(type_name, diff_type)                                             \
		type_name operator+ (diff_type offset) const { type_name tmp(*this); return tmp.operator+=(offset); }  \
		INLINE type_name& operator++ () { return operator+=(1); }                                              \
		type_name operator++ (int) { type_name tmp(*this); this->operator++(); return tmp; }

#define DECLARE_CANONICAL_ADDITION_OPERATORS_NOPOST(type_name, diff_type)                                      \
		type_name operator+ (diff_type offset) const { type_name tmp(*this); return tmp.operator+=(offset); }  \
		INLINE type_name& operator++ () { return operator+=(1); }                                              \
		type_name operator++ (int) = delete; // NO postfix!

#define DECLARE_CANONICAL_SUBTRACTION_OPERATORS(type_name, diff_type)                                   \
		type_name operator- (diff_type offset) const { type_name tmp(*this); return tmp.operator-=(offset); }  \
		INLINE type_name& operator-- () { return operator-=(1); }                                              \
		type_name operator-- (int) { type_name tmp(*this); this->operator--(); return tmp; }

#define DECLARE_CANONICAL_SUBTRACTION_OPERATORS_NOPOST(type_name, diff_type)                                   \
		type_name operator- (diff_type offset) const { type_name tmp(*this); return tmp.operator-=(offset); }  \
		INLINE type_name& operator-- () { return operator-=(1); }                                              \
		type_name operator-- (int) = delete; // NO postfix!
