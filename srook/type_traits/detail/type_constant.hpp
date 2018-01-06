#ifndef INCLUDED_SROOK_TYPE_TRAITS_DETAIL_TYPE_CONSTANT_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_DETAIL_TYPE_CONSTANT_HPP
#include <srook/type_traits/enable_if.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T>
struct type_constant : srook::enable_if<true, T> {};

} // namespace detail

using detail::type_constant;

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::type_constant;

} // namespace srook

#endif
