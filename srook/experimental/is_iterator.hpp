#ifndef INCLUDE_SROOK_TYPE_TRAITS_IS_ITERATOR
#define INCLUDE_SROOK_TYPE_TRAITS_IS_ITERATOR
#include<type_traits>
#include<iterator>
#include<srook/type_traits/has_iterator.hpp>

namespace srook{
namespace experimental{

inline namespace mpl{
inline namespace v1{

template<class,class=std::void_t<>>
constexpr bool is_iterator_v = std::false_type::value;

template<class T>
constexpr bool is_iterator_v<T,std::enable_if_t<std::is_base_of<std::iterator<typename T::iterator_category,void,void,void,void>,T>::value>> = std::true_type::value;

template<class T>
constexpr bool is_iterator_v<T,srook::enable_if_t<has_iterator_category_v<T>>> = std::true_type::value;

} // inline namespace v1
} // inline namespace mpl
} // namespace experimental
} // namespace srook
#endif
