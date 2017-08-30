// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_PACK_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_PACK_HPP
#include <cstddef>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/inline_variable.hpp>

namespace srook {
inline namespace mpl {
inline namespace v1 {
namespace detail {
template <class... T>
struct pack {
    SROOK_INLINE_VARIABLE static constexpr std::size_t size = sizeof...(T);
};
} // namespace detail

using detail::pack;

} // namespace v1
} // namespace mpl
} // namespace srook
#endif
