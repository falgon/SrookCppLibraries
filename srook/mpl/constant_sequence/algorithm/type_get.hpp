#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_TYPE_GET_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_TYPE_GET_HPP
#include<utility>
#include<srook/utility/integer_sequence.hpp>
#include<srook/config/compiler.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{

template<class>
struct type_get;

template<class T,T... v>
struct type_get<srook::integer_sequence<T,v...>>{
	using type = T;
};

#ifndef SROOK_IS_CXX11_EARLIER

template<class T,T... v>
struct type_get<std::integer_sequence<T,v...>>{
	using type = T;
};

template<class T>
using type_get_t = typename type_get<T>::type;

#endif

} // namespace constant_sequence
} // namespace inline namespace mpl
} // namespace srook

#endif
