// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDE_SROOK_TYPE_TRAITS_HAS_ITERATOR
#define INCLUDE_SROOK_TYPE_TRAITS_HAS_ITERATOR
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#if 0
#include <iterator>
#include <srook/config/compiler_version.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/is_base_of.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/utility/void_t.hpp>
#include <type_traits>
namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class, class = typename srook::voider<>::type>
struct has_iterator_category : SROOK_FALSE_TYPE {};
template <class T>
struct has_iterator_category<T, typename voider<typename T::iterator_category>::type > : SROOK_TRUE_TYPE {};

template <class, class = typename srook::voider<>::type>
struct has_iterator : SROOK_FALSE_TYPE {};
template <class T>
struct has_iterator<T, typename voider<typename T::iterator, enable_if_t<!has_iterator_category<T>::value> >::type> : SROOK_TRUE_TYPE {};
template <class T>
struct has_iterator<
    T,
    typename enable_if<has_iterator_category<T>::value>::type> : conditional<is_base_of<std::iterator<typename T::iterator_category, void, void, void, void>, T>::value || experimental::is_iterator_v<T>,
#ifdef SROOK_GCC_VERSION
#    if SROOK_GCC_VERSION > 619
                                                                                       SROOK_FALSE_TYPE, SROOK_TRUE_TYPE
#    else
                                                                                       SROOK_TRUE_TYPE, SROOK_FALSE_TYPE // not support
#    endif

#elif defined(SROOK_CLANG_VERSION)
#    if SROOK_CLANG_VERSION > 380
                                                                                       SROOK_FALSE_TYPE, SROOK_TRUE_TYPE
#    else
                                                                                       SROOK_TRUE_TYPE, SROOK_FALSE_TYPE // deprecate
#    endif

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
} // namespace srooka
#else

#include <srook/config.hpp>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <srook/type_traits/detail/sfinae_types.hpp>
#include <srook/type_traits/conditional.hpp>

SROOK_NESTED_NAMESPACE(srook, type_traits) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct has_iterator : sfinae_types {
private:
    template <class U>
    static SROOK_DEDUCED_TYPENAME conditional<
        srook::type_traits::is_iterator<SROOK_DEDUCED_TYPENAME U::iterator>::value, one, two
    >::type
    test(SROOK_DEDUCED_TYPENAME U::iterator*);
    
    template <class U>
    static two test(...);
public:
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool value = sizeof(test<T>(0)) == sizeof(one);
};

} // namespace detail

template <class T>
struct has_iterator : detail::has_iterator<T> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool has_iterator_v = has_iterator<T>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(type_traits, srook)

namespace srook {

using srook::type_traits::has_iterator;

} // namespace srook

#endif
#endif
#endif
