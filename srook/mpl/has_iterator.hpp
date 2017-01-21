#ifndef INCLUDE_SROOK_TYPE_TRAITS_HAS_ITERATOR
#define INCLUDE_SROOK_TYPE_TRAITS_HAS_ITERATOR
#include<type_traits>
namespace srook{
namespace mpl{
inline namespace v1{

template<class,class=std::void_t<>>
bool has_iterator_v=std::false_type::value;
template<class T>
bool has_iterator_v<T,std::void_t<typename T::iterator>> =std::true_type::value;

} // inline namespace v1
} // namespace mpl
} // namespace srook
#endif
