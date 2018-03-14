// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ITERATOR_IS_OUTPUTITERATOR_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ITERATOR_IS_OUTPUTITERATOR_HPP
#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/is_class.hpp>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <srook/type_traits/is_copy_assignable.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct is_outputiterator_requires {
private:
    template <class U>
    static SROOK_DEDUCED_TYPENAME type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME is_same<SROOK_DECLTYPE(++declval<U&>()), U&>::type,
        is_convertible<SROOK_DECLTYPE(declval<U&>()++), const U&>,
        is_copy_assignable<U&>
    >::type test(const U&);
    static SROOK_FALSE_TYPE test(...);
public:
    typedef type_traits::detail::Land<
        SROOK_DECLTYPE(test(declval<T>())), type_traits::detail::Lor<is_class<T>, is_pointer<T>>, is_iterator<T>
    > type;
};

} // namespace detail

template <class T>
struct is_outputiterator : detail::is_outputiterator_requires<T>::type {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_CONSTEXPR bool is_outputiterator_v = is_outputiterator<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using type_traits::is_outputiterator;

} // namespace srook

#endif
