// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ITERATOR_IS_RANDOMACCESSITERATOR_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ITERATOR_IS_RANDOMACCESSITERATOR_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/iterator/is_bidirectionaliterator.hpp>
#include <srook/type_traits/is_pointer.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct is_randomaccessiterator_requires {
private:
    template <class U>
    static SROOK_DEDUCED_TYPENAME 
    type_traits::detail::Land<
        is_same<SROOK_DECLTYPE(declval<U&>() += declval<SROOK_DEDUCED_TYPENAME std::iterator_traits<U>::difference_type>()), U&>,
        is_same<SROOK_DECLTYPE(declval<U>() + declval<SROOK_DEDUCED_TYPENAME std::iterator_traits<U>::difference_type>()), U>,
        is_same<SROOK_DECLTYPE(declval<SROOK_DEDUCED_TYPENAME std::iterator_traits<U>::difference_type>() + declval<U>()), U>,
        is_same<SROOK_DECLTYPE(declval<U&>() -= declval<SROOK_DEDUCED_TYPENAME std::iterator_traits<U>::difference_type>()), U&>,
        is_same<SROOK_DECLTYPE(declval<U>() - declval<SROOK_DEDUCED_TYPENAME std::iterator_traits<U>::difference_type>()), U>,
        is_same<SROOK_DECLTYPE(declval<U>() - declval<U>()), SROOK_DEDUCED_TYPENAME std::iterator_traits<U>::difference_type>,
        is_convertible<SROOK_DECLTYPE(declval<U&>()[declval<SROOK_DEDUCED_TYPENAME std::iterator_traits<U>::difference_type>()]), SROOK_DEDUCED_TYPENAME std::iterator_traits<U>::reference>,
        is_convertible<SROOK_DECLTYPE(declval<U>() < declval<U>()), bool>,
        is_convertible<SROOK_DECLTYPE(declval<U>() > declval<U>()), bool>,
        is_convertible<SROOK_DECLTYPE(declval<U>() <= declval<U>()), bool>,
        is_convertible<SROOK_DECLTYPE(declval<U>() >= declval<U>()), bool>
    >::type
    test(const U&);

    static SROOK_FALSE_TYPE test(...);
public:
    typedef type_traits::detail::Lor<
        is_pointer<T>,
        type_traits::detail::Land<
            is_bidirectionaliterator<T>, 
            SROOK_DECLTYPE(test(declval<T>()))
        >
    >
    type;
};

} // namespace detail

template <class T>
struct is_randomaccessiterator : type_traits::detail::Lor<is_pointer<T>, SROOK_DEDUCED_TYPENAME detail::is_randomaccessiterator_requires<T>::type> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_CONSTEXPR bool is_randomaccessiterator_v = is_randomaccessiterator<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using type_traits::is_randomaccessiterator;

} // namespace srook

#endif
