// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_TYPETRAITS_ADD_POINTER_HPP
#define INCLUDED_SROOK_MPL_TYPETRAITS_ADD_POINTER_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T>
struct add_pointer {
    typedef T* type;
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::add_pointer;

#if SROOK_CPP_ALIAS_TEMPLATES

template <class T>
using add_pointer_t = typename type_traits::detail::add_pointer<T>::type;

#endif

} // namespace srook
#endif
