// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ITERATOR_IS_FORWARDITERATOR_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ITERATOR_IS_FORWARDITERATOR_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/iterator/is_inputiterator.hpp>
#include <srook/type_traits/iterator/is_outputiterator.hpp>
#include <srook/type_traits/is_default_constructible.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct is_forwarditerator_requires {
private:
    template <class U>
    static SROOK_DEDUCED_TYPENAME 
    type_traits::detail::Land<is_same<SROOK_DECLTYPE(declval<U&>()++), U>, is_same<SROOK_DECLTYPE(*declval<U&>()++), SROOK_DEDUCED_TYPENAME std::iterator_traits<U>::reference>>::type
    test(const U&);

    static SROOK_FALSE_TYPE test(...);
public:
    typedef type_traits::detail::Land<
        is_inputiterator<T>, 
        is_default_constructible<T>, 
        SROOK_DEDUCED_TYPENAME conditional<
            is_outputiterator<T>::value,
            is_same<SROOK_DEDUCED_TYPENAME std::iterator_traits<T>::reference, SROOK_DEDUCED_TYPENAME std::iterator_traits<T>::value_type&>,
            is_same<SROOK_DEDUCED_TYPENAME std::iterator_traits<T>::reference, const SROOK_DEDUCED_TYPENAME std::iterator_traits<T>::value_type&>
        >::type,
        SROOK_DECLTYPE(test(declval<T>()))
    > type;
};

} // namespace detail

template <class T>
struct is_forwarditerator : detail::is_forwarditerator_requires<T>::type {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_CONSTEXPR bool is_forwarditerator_v = is_forwarditerator<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using type_traits::is_forwarditerator;

} // namespace srook

#endif
