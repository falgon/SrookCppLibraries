// Copyright (C) 2017 roki
#ifdef __cplusplus
#ifndef INCLUDED_SROOK_CONFIG_REQUIRE_REQUIRE_CORE_HPP
#define INCLUDED_SROOK_CONFIG_REQUIRE_REQUIRE_CORE_HPP
#include <srook/config/compiler.hpp>
#include <srook/type_traits/enable_disable_if.hpp>

#ifdef POSSIBLE_TO_INCLUDE_STD_ENABLE_IF
#if !defined(SROOK_NO_CXX11_NULLPTR) || !defined(BOOST_NO_CXX11_NULLPTR)
#define VARIADIC_REQUIRES(...) typename std::enable_if<static_cast<bool>((__VA_ARGS__ + ...)), std::nullptr_t>::type = nullptr
#define REQUIRES(...) typename std::enable_if<__VA_ARGS__, std::nullptr_t>::type = nullptr
#else
#define VARIADIC_REQUIRES(...) typename std::enable_if_t<static_cast<bool>((__VA_ARGS__ + ...))>::type * = static_cast<void *>(0)
#define REQUIRES(...) typename std::enable_if<__VA_ARGS__>::type * = static_cast<void *>(0)
#endif

#elif defined(POSSIBLE_TO_INCLUDE_BOOST_ENABLE_IF)
#if !defined(SROOK_NO_CXX11_NULLPTR) || !defined(BOOST_NO_CXX11_NULLPTR)
#define VARIADIC_REQUIRES(...) typename boost::enable_if_c<static_cast<bool>((__VA_ARGS__ + ...)), std::nullptr_t>::type = nullptr
#define REQUIRES(...) typename boost::enable_if_c<__VA_ARGS__, std::nullptr_t>::type = nullptr
#else
#define VARIADIC_REQUIRES(...) typename boost::enable_if_c<static_cast<bool>((__VA_ARGS__ + ...))>::type * = static_cast<void *>(0)
#define REQUIRES(...) typename boost::enable_if_c<__VA_ARGS__>::type * = static_cast<void *>(0)
#endif

#else
#if !defined(SROOK_NO_CXX11_NULLPTR) || !defined(BOOST_NO_CXX11_NULLPTR)
#define VARIADIC_REQUIRES(...) typename srook::enable_if<static_cast<bool>((__VA_ARGS__ + ...))>::type = nullptr
#define REQUIRES(...) typename srook::enable_if<__VA_ARGS__>::type = nullptr
#else
#define VARIADIC_REQUIRES(...) typename srook::enable_if<static_cast<bool>((__VA_ARGS__ + ...)), void *>::type = static_cast<void *>(0)
#define REQUIRES(...) typename srook::enable_if<__VA_ARGS__, void *>::type = static_cast<void *>(0)
#endif
#endif

#endif
#endif
