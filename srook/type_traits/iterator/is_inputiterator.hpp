// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ITERATOR_IS_INPUTITERATOR_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ITERATOR_IS_INPUTITERATOR_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <srook/type_traits/is_equality_comparable.hpp>
#include <srook/type_traits/is_postincrementable.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct is_inputiterator_requires {
private:
    template <class U>
    static SROOK_DECLTYPE(*declval<U&>()++, SROOK_TRUE_TYPE()) test(const U&);
    static SROOK_FALSE_TYPE test(...);
public:
    typedef type_traits::detail::Land<SROOK_DECLTYPE(test(declval<T>())), is_preincrementable<T>, is_postincrementable<T>, is_dereferenceable<T>> type;
};

} // namespace detail

template <class T>
struct is_inputiterator : detail::is_inputiterator_requires<T>::type {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_CONSTEXPR bool is_inputiterator_v = is_inputiterator<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using type_traits::is_inputiterator;
using type_traits::is_inputiterator_v;

} // namespace srook

#endif
