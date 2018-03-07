// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_NUMERIC_ALGORITHM_DETAIL_CONFIG_HPP
#define INCLUDED_SROOK_NUMERIC_ALGORITHM_DETAIL_CONFIG_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/cxx20/concepts/iterator/Iterator.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_pointer.hpp>
#include <srook/tmpl/vt/is_contained_in.hpp>
#include <srook/utility/void_t.hpp>
#include <iterator>

#ifdef __GNUC__
#   pragma GCC system_header
#elif defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang ignored "-Wvariadic-macros"
#endif

SROOK_NESTED_NAMESPACE(srook, numeric, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, class = SROOK_DEDUCED_TYPENAME voider<>::type>
struct arithmetic_iter_category_accessible 
    : SROOK_FALSE_TYPE {};
template <class T>
struct arithmetic_iter_category_accessible<T, SROOK_DEDUCED_TYPENAME voider<SROOK_DEDUCED_TYPENAME std::iterator_traits<T>::iterator_category>::type>
    : SROOK_TRUE_TYPE {};

template <class T, class = SROOK_DEDUCED_TYPENAME voider<>::type>
struct is_arithmetic_addable_iter
    : type_traits::detail::Lor<
        is_pointer<T>, 
        type_traits::detail::Lnot<
            tmpl::vt::is_contained_in<SROOK_DEDUCED_TYPENAME std::iterator_traits<T>::iterator_category, std::forward_iterator_tag, std::bidirectional_iterator_tag>
        >
    > {};

#if SROOK_HAS_CONCEPTS
template <class T>
SROOK_CONCEPT NumericAlgoValidIter = srook::concepts::Iterator<T> || is_pointer<T>::value;
#   define SROOK_ARITHMETIC_ITER detail::NumericAlgoValidIter
#   define SROOK_ARITHMETIC_ITER_REQUIRES(X) SROOK_TRUE_TYPE
#else
#   define SROOK_ARITHMETIC_ITER class
#   define SROOK_ARITHMETIC_ITER_REQUIRES(X) detail::arithmetic_iter_category_accessible<X>
#endif

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, numeric, srook)

#ifdef __clang__
#   pragma clang  diagnostic pop
#endif
#endif
