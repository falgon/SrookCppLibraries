// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_TYPETRAITS_ADD_CV_HPP
#define INCLUDED_SROOK_MPL_TYPETRAITS_ADD_CV_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/add_const.hpp>
#include <srook/type_traits/add_volatile.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T>
struct add_cv {
    typedef typename add_volatile<typename add_const<T>::type>::type type;
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::add_cv;

#if SROOK_CPP_ALIAS_TEMPLATES

template <class T>
using add_cv_t = typename type_traits::detail::add_cv<T>::type;

#endif

} // namespace srook
#endif
