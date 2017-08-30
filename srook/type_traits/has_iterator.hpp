// Copyright (C) 2017 roki
#ifndef INCLUDE_SROOK_TYPE_TRAITS_HAS_ITERATOR
#define INCLUDE_SROOK_TYPE_TRAITS_HAS_ITERATOR
#include <iterator>
#include <srook/config/compiler_version.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/experimental/is_iterator.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/utility/void_t.hpp>
#include <type_traits>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class, class = typename srook::voider<>::type>
struct has_iterator_category : SROOK_FALSE_TYPE {
};
template <class T>
struct has_iterator_category<T, std::void_t<typename T::iterator_category>> : SROOK_TRUE_TYPE {
};

template <class, class = typename srook::voider<>::type>
struct has_iterator : SROOK_FALSE_TYPE {
};
template <class T>
struct has_iterator<T, typename srook::voider<typename T::iterator, std::enable_if_t<!has_iterator_category<T>::value>>::type> : SROOK_TRUE_TYPE {
};
template <class T>
struct has_iterator<
    T,
    typename std::enable_if<has_iterator_category<T>::value>::type> : std::conditional<std::is_base_of<std::iterator<typename T::iterator_category, void, void, void, void>, T>::value ||
											   experimental::is_iterator_v<T>,
#ifdef SROOK_GCC_VERSION
#if SROOK_GCC_VERSION > 619
										       SROOK_FALSE_TYPE, SROOK_TRUE_TYPE
#else
										       SROOK_TRUE_TYPE, SROOK_FALSE_TYPE // not support
#endif

#elif defined(SROOK_CLANG_VERSION)
#if SROOK_CLANG_VERSION > 380
										       SROOK_FALSE_TYPE, SROOK_TRUE_TYPE
#else
										       SROOK_TRUE_TYPE, SROOK_FALSE_TYPE // deprecate
#endif

#elif !defined(SROOK_CLANG_VERSION) && !defined(SROOK_GCC_VERSION) && defined(__APPLE__) // deprecate
										       SROOK_FALSE_TYPE, SROOK_TRUE_TYPE
#endif
										       >::type {
};
} // namespace detail

using detail::has_iterator;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class Default = typename srook::voider<>::type>
constexpr bool has_iterator_v = detail::has_iterator<T, Default>::value;
#endif

SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END
} // namespace srook
#endif
