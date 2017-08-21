// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_REQUIRE_REQUIRE_CORE_HPP
#define INCLUDED_SROOK_CONFIG_REQUIRE_REQUIRE_CORE_HPP
#include<srook/config/libraries/nullptr.hpp>
#include<srook/type_traits/enable_disable_if.hpp>

#define VARIADIC_REQUIRES(...) typename srook::enable_if<static_cast<bool>((__VA_ARGS__ + ...)), SROOK_NULLPTR_T>::type = SROOK_NULLPTR
#define REQUIRES(...) typename srook::enable_if<__VA_ARGS__, SROOK_NULLPTR_T>::type = SROOK_NULLPTR

#endif
