// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_REQUIRE_REQUIRE_CORE_HPP
#define INCLUDED_SROOK_CONFIG_REQUIRE_REQUIRE_CORE_HPP
#include <srook/config/libraries/nullptr.hpp>
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature/deduced_typename.hpp>
#include <srook/type_traits/enable_if.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#define VARIADIC_REQUIRES(...)\
   	SROOK_DEDUCED_TYPENAME srook::enable_if<static_cast<bool>((__VA_ARGS__ + ...)), SROOK_NULLPTR_T>::type = SROOK_NULLPTR
#define REQUIRES(...)\
   	SROOK_DEDUCED_TYPENAME srook::enable_if<__VA_ARGS__, SROOK_NULLPTR_T>::type = SROOK_NULLPTR
#define SROOK_VARIADIC_REQUIRES(...) VARIADIC_REQUIRES(__VA_ARGS__)
#define SROOK_REQUIRES(...) REQUIRES(__VA_ARGS__)
#else
#define REQUIRES(...)\
	SROOK_DEDUCED_TYPENAME srook::enable_if<__VA_ARGS__, SROOK_NULLPTR_T>::type
#endif
#endif
