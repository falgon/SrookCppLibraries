// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_UTILITY_CHECKED_DELETE_HPP
#define INCLUDED_SROOK_MEMORY_UTILITY_CHECKED_DELETE_HPP

#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/static_assert.hpp>
#include <srook/config/attribute/deprecated.hpp>
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/libraries/nullptr.hpp>
#if !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
#	include <functional>
#endif

namespace srook {
namespace memory {
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
SROOK_FORCE_INLINE void checked_delete(const T* x)
{
	SROOK_STATIC_ASSERT(sizeof(T), "The type must be complete");
	if(x){
		delete x;
		x = SROOK_NULLPTR;
	}
}

template <class T
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
= void
#endif
>
struct checked_deleter
#if !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
: std::unary_function<T*, void>
#endif
{
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
#	define SROOK_DETECT_AND_DEPRECATE(x) SROOK_DEPRECATED_MESSAGE(#x"is deprecated until C++17 mode")
#else
#	define SROOK_DETECT_AND_DEPRECATE(x)
#endif
	typedef SROOK_DETECT_AND_DEPRECATE(result_type) void result_type;
	typedef SROOK_DETECT_AND_DEPRECATE(argument_type) T* argument_type;
#undef SROOK_DETECT_AND_DEPRECATE
	inline void operator()(T* x) const { checked_delete(x); }
};

template<>
struct checked_deleter<void> {
	struct is_transparent{};
	template <class T>
	inline void operator()(T* x) const { checked_delete(x); }
};

SROOK_INLINE_NAMESPACE_END
} // namespace utility

using utility::checked_delete;
using utility::checked_deleter;

} // namespace memory

using memory::checked_delete;
using memory::checked_deleter;

} // namespace srook

#endif
