// Copyright (C) 2017 roki
#ifndef INCLUDE_SROOK_TYPE_TRAITS_IS_ITERATOR
#define INCLUDE_SROOK_TYPE_TRAITS_IS_ITERATOR
#include<type_traits>
#include<iterator>

namespace srook{
namespace experimental{

inline namespace mpl{
inline namespace v1{

template<class,class=std::void_t<>>
constexpr bool has_iterator_category_v=std::false_type::value;
template<class T>
constexpr bool has_iterator_category_v<T,std::void_t<typename T::iterator_category>> =std::true_type::value;

template<class,class=std::void_t<>>
constexpr bool has_value_type_v=std::false_type::value;
template<class T>
constexpr bool has_value_type_v<T,std::void_t<typename T::value_type>> =std::true_type::value;

template<class,class=std::void_t<>>
constexpr bool has_difference_type_v=std::false_type::value;
template<class T>
constexpr bool has_difference_type_v<T,std::void_t<typename T::difference_type>> =std::true_type::value;

template<class,class=std::void_t<>>
constexpr bool has_pointer_v=std::false_type::value;
template<class T>
constexpr bool has_pointer_v<T,std::void_t<typename T::pointer>> =std::true_type::value;

template<class,class=std::void_t<>>
constexpr bool has_reference_v=std::false_type::value;
template<class T>
constexpr bool has_reference_v<T,std::void_t<typename T::reference>> =std::true_type::value;

template<class T>
constexpr bool has_iterators_types_v=
	std::conditional<
		(has_iterator_category_v<T> && has_value_type_v<T>&& has_difference_type_v<T> && has_pointer_v<T> && has_reference_v<T>),
		std::true_type,
		std::false_type
	>::type::value;


template<class,class=std::void_t<>>
constexpr bool is_iterator_v = std::false_type::value;

template<class T>
constexpr bool is_iterator_v<
	T,
	std::enable_if_t<
		std::is_base_of<std::iterator<typename T::iterator_category,void,void,void,void>,T>::value ||
		has_iterators_types_v<T>
	>
> = std::true_type::value;

} // inline namespace v1
} // inline namespace mpl
} // namespace experimental
} // namespace srook
#endif
