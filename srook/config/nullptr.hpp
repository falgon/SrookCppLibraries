// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_NULLPTR_T
#define INCLUDED_SROOK_CONFIG_NULLPTR_T

#include <cstddef>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/feature/delete.hpp>

#if !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT) && !defined(nullptr)
namespace srook {
namespace cxx03 {

const class nullptr_t{
public:
	template <class T>
	operator T*() const { return NULL; }

	template <class C, class T>
	operator T C::*() const { return NULL; }
private:
	void operator&() SROOK_EQ_DELETE
} nullptr = {};

} // namespace cxx03
} // namespace srook

#	define SROOK_NULLPTR_T srook::cxx03::nullptr_t
#	define SROOK_NULLPTR srook::cxx03::nullptr
#elif defined(nullptr)
#	include <srook/config/feature/decltype.hpp>
#	define SROOK_NULLPTR nullptr
#	define SROOK_NULLPTR_T SROOK_DECLTYPE(nullptr)
#else
#	define SROOK_NULLPTR_T std::nullptr_t
#	define SROOK_NULLPTR nullptr
#endif

#endif
