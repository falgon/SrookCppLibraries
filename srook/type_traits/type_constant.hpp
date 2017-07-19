#ifndef INCLUDED_SROOK_TYPE_TRAITS_TYPE_CONSTANT_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_TYPE_CONSTANT_HPP
#include<type_traits>

namespace srook{

template<class T>
struct type_constant : std::enable_if<true,T>{};

} // namespace srook

#endif
