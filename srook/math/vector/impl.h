#ifndef INCLUDED_SROOK_MATH_VECTOR_IMPL_H
#define INCLUDED_SROOK_MATH_VECTOR_IMPL_H

#include <srook/config.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/tmpl/vt/at.hpp>

SROOK_NESTED_NAMESPACE(srook, math) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class...>
class vector_impl;

template <class... Xs>
struct is_onemore : bool_constant<(sizeof...(Xs) > 0)> {};

template <std::size_t I>
struct index_bind {
    template <class... Ts>
    struct generate : tmpl::vt::at<I, Ts...> {};
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(math, srook)
#endif
