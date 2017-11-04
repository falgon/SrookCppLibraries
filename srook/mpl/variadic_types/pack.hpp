// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_PACK_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_PACK_HPP
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <cstddef>
#include <srook/config/inline_variable.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/config/feature/constexpr.hpp>

namespace srook {
inline namespace mpl {
inline namespace v1 {
namespace detail {
template <class... T>
struct pack {
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR_OR_CONST std::size_t size = sizeof...(T);
};
} // namespace detail

using detail::pack;

} // namespace v1
} // namespace mpl
} // namespace srook
#endif
#endif
