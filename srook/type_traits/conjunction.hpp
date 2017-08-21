// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_CONJUNCTION_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_CONJUNCTION_HPP
#include <type_traits>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/inline_variable.hpp>

namespace srook {

template <class...>
struct conjunction : std::true_type {
};

template <class B1>
struct conjunction<B1> : B1 {
};

template <class B1, class... Bn>
struct conjunction<B1, Bn...> : std::conditional<bool(B1::value), conjunction<Bn...>, B1>::type {
};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... B>
SROOK_INLINE_VARIABLE constexpr bool conjunction_v = conjunction<B...>::value;
#endif

} // namespace srook
#endif
