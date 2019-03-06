// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDE_SROOK_TYPE_TRAITS_IS_ITERATOR
#define INCLUDE_SROOK_TYPE_TRAITS_IS_ITERATOR
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <iterator>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/utility/void_t.hpp>
#include <type_traits>

namespace srook {
namespace experimental {

inline namespace mpl {
inline namespace v1 {

template <class, class = typename voider<>::type>
constexpr bool has_iterator_category_v = SROOK_FALSE_TYPE::value;
template <class T>
constexpr bool has_iterator_category_v<T, typename voider<typename T::iterator_category>::type> = SROOK_TRUE_TYPE::value;

template <class, class = typename voider<>::type>
constexpr bool has_value_type_v = SROOK_FALSE_TYPE::value;
template <class T>
constexpr bool has_value_type_v<T, typename voider<typename T::value_type>::type> = SROOK_TRUE_TYPE::value;

template <class, class = typename voider<>::type>
constexpr bool has_difference_type_v = SROOK_FALSE_TYPE::value;
template <class T>
constexpr bool has_difference_type_v<T, typename voider<typename T::difference_type>::type> = SROOK_TRUE_TYPE::value;

template <class, class = typename voider<>::type>
constexpr bool has_pointer_v = SROOK_FALSE_TYPE::value;
template <class T>
constexpr bool has_pointer_v<T, typename voider<typename T::pointer>::type> = SROOK_TRUE_TYPE::value;

template <class, class = typename voider<>::type>
constexpr bool has_reference_v = SROOK_FALSE_TYPE::value;
template <class T>
constexpr bool has_reference_v<T, typename voider<typename T::reference>::type> = SROOK_TRUE_TYPE::value;

template <class T>
constexpr bool has_iterators_types_v = conditional<
    (has_iterator_category_v<T> && has_value_type_v<T> && has_difference_type_v<T> && has_pointer_v<T> && has_reference_v<T>),
    SROOK_TRUE_TYPE,
    SROOK_FALSE_TYPE>::type::value;

template <class, class = typename voider<>::type>
constexpr bool is_iterator_v = SROOK_FALSE_TYPE::value;

template <class T>
constexpr bool is_iterator_v<
    T,
    typename enable_if<
        std::is_base_of<std::iterator<typename T::iterator_category, void, void, void, void>, T>::value || has_iterators_types_v<T> >::type > = SROOK_TRUE_TYPE::value;

} // namespace v1
} // namespace mpl
} // namespace experimental
} // namespace srook
#endif
#endif
