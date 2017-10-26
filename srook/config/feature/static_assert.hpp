// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_STATIC_ASSERT_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_STATIC_ASSERT_HPP

#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/preprocessor/concat.hpp>

#if SROOK_CPP_STATIC_ASSERT
#	define SROOK_STATIC_ASSERT(x, y) static_assert(x, y)
#elif defined(__clang__)
#	define SROOK_STATIC_ASSERT(x, y) static_assert(x, y)
#elif defined(__has_extension)
#	if __has_extension(c_static_assert)
#		define SROOK_STATIC_ASSERT(x, y) _Static_assert(x, y)
#	endif
#else

extern "C++" {
	template <bool> struct static_assert_test;
	template <> struct static_assert_test<true> {};
	template <unsigned> struct static_assert_check {};
}

#define SROOK_STATIC_ASSERT(x, y)\
	typedef static_assert_check<sizeof(static_assert_test<(x)>)>\
	SROOK_CONCAT(__t, SROOK_LINE)
#endif

#endif
