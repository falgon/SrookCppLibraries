// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ITERATOR_IS_BIDIRECTIONALITERATOR_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ITERATOR_IS_BIDIRECTIONALITERATOR_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/is_pointer.hpp>
#include <srook/type_traits/iterator/is_forwarditerator.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct is_bidirectionaliterator_requires {
private:
    template <class U>
    static SROOK_DEDUCED_TYPENAME 
    type_traits::detail::Land<
        is_same<SROOK_DECLTYPE(--declval<U&>()), U&>, 
        is_convertible<SROOK_DECLTYPE(declval<U&>()--), const U&>, 
        is_same<SROOK_DECLTYPE(*declval<U>()--), SROOK_DEDUCED_TYPENAME std::iterator_traits<U>::reference>
    >::type
    test(const U&);

    static SROOK_FALSE_TYPE test(...);
public:
    typedef type_traits::detail::Lor<
        is_pointer<T>,
        type_traits::detail::Land<
            is_forwarditerator<T>, 
            SROOK_DECLTYPE(test(declval<T>()))
        >
    > type;
};

} // namespace detail

template <class T>
struct is_bidirectionaliterator : detail::is_bidirectionaliterator_requires<T>::type {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_CONSTEXPR bool is_bidirectionaliterator_v = is_bidirectionaliterator<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using type_traits::is_bidirectionaliterator;

} // namespace srook

#endif
