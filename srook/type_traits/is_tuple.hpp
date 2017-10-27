// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITAS_IS_TUPLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITAS_IS_TUPLE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/utility/void_t.hpp>
#include <tuple>
#include <type_traits>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class, class = typename voider<>::type>
struct is_tuple : SROOK_FALSE_TYPE {
};

template <class T>
struct is_tuple<T, typename voider<decltype(std::tuple_size<std::decay_t<T> >::value)>::type> : SROOK_TRUE_TYPE {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::is_tuple;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class V = typename voider<>::type>
constexpr bool is_tuple_v = type_traits::detail::is_tuple<T, V>::value;
#endif

} // namespace srook
#endif
