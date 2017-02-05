#ifndef INCLUDE_SROOK_TYPE_TRAITS_HAS_ITERATOR
#define INCLUDE_SROOK_TYPE_TRAITS_HAS_ITERATOR
#include<type_traits>
#include<iterator>

namespace srook{
inline namespace mpl{
inline namespace v1{

template<class,class=std::void_t<>>
constexpr bool has_iterator_category_v = std::false_type::value;
template<class T>
constexpr bool has_iterator_category_v<T,std::void_t<typename T::iterator_category>> = std::true_type::value;

template<class,class=std::void_t<>>
constexpr bool has_iterator_v = std::false_type::value;

template<class T>
constexpr bool has_iterator_v<
	T,
	std::void_t<
		typename T::iterator,
		std::enable_if_t<!has_iterator_category_v<T>>
	>
> = std::true_type::value;

template<class T>
constexpr bool has_iterator_v<
	T,
	std::enable_if_t<has_iterator_category_v<T>>
> = std::conditional<
		std::is_base_of<
			std::iterator<typename T::iterator_category,void,void,void,void>,T
		>::value,
		std::true_type,
		std::false_type
>::type::value;

} // inline namespace v1
} // inline namespace mpl
} // namespace srook
#endif
