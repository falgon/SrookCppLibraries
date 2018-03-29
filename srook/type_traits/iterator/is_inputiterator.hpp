// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ITERATOR_IS_INPUTITERATOR_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ITERATOR_IS_INPUTITERATOR_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/is_pointer.hpp>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <srook/type_traits/is_equality_comparable.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct equality_compare_to_bool {
private:
    template <class U>
    static SROOK_DEDUCED_TYPENAME is_convertible<SROOK_DECLTYPE(declval<U&>() != declval<U&>()), bool>::type test(const U&);
    static SROOK_FALSE_TYPE test(...);
public:
    static SROOK_CONSTEXPR bool value = SROOK_DECLTYPE(test(declval<T>()))::value;
};

template <class T>
struct dereferenceable_to_ref {
private:
    template <class U>
    static SROOK_DEDUCED_TYPENAME 
    type_traits::detail::Land<
        is_same<SROOK_DECLTYPE(*declval<U&>()), SROOK_DEDUCED_TYPENAME std::iterator_traits<U>::reference>,
        is_convertible<SROOK_DECLTYPE(*declval<U&>()), SROOK_DEDUCED_TYPENAME std::iterator_traits<U>::value_type>
    >::type
    test(const U&);

    static SROOK_FALSE_TYPE test(...);
public:
    static SROOK_CONSTEXPR bool value = SROOK_DECLTYPE(test(declval<T>()))::value;
};

template <class T>
struct postincrement_to_value_type {
private:
    template <class U>
    static SROOK_DEDUCED_TYPENAME is_convertible<SROOK_DECLTYPE(*declval<U&>()++), SROOK_DEDUCED_TYPENAME std::iterator_traits<U>::value_type>::type
    test(const U&);
    static SROOK_FALSE_TYPE test(...);
public:
    static SROOK_CONSTEXPR bool value = SROOK_DECLTYPE(test(declval<T>()))::value;
};

template <class T>
struct is_inputiterator_requires {
private:
    template <class U>
    static SROOK_DECLTYPE(*declval<U&>()++, SROOK_TRUE_TYPE()) test(const U&);
    static SROOK_FALSE_TYPE test(...);
public:
    typedef 
        type_traits::detail::Land<
            is_iterator<T>,
            SROOK_DECLTYPE(test(declval<T>())), 
            equality_compare_to_bool<T>,
            dereferenceable_to_ref<T>
        >
    type;
};

} // namespace detail

template <class T>
struct is_inputiterator : type_traits::detail::Lor<is_pointer<T>, SROOK_DEDUCED_TYPENAME detail::is_inputiterator_requires<T>::type> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_CONSTEXPR bool is_inputiterator_v = is_inputiterator<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using type_traits::is_inputiterator;

} // namespace srook

#endif
