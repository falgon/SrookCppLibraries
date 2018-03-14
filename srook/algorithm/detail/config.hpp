// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_DETAIL_CONFIG_HPP
#define INCLUDED_SROOK_ALGORITHM_DETAIL_CONFIG_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/tmpl/vt/apply.hpp>
#include <srook/tmpl/vt/map.hpp>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <iterator>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, bool>
struct deref_iter_impl : type_constant<T> {};
template <class T>
struct deref_iter_impl<T, true> : type_constant<SROOK_DEDUCED_TYPENAME std::iterator_traits<T>::reference> {};
template <class>
struct deref_iter;
template <class T>
struct deref_iter : deref_iter_impl<T, is_iterator<T>::value> {};

template <template <class...> class Check, class... Ts>
struct iter_ref_apply : 
    srook::tmpl::vt::apply<Check, SROOK_DEDUCED_TYPENAME srook::tmpl::vt::map<deref_iter, Ts...>::type> {};

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
