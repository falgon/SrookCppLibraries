#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ALGORITHM_SIZE_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ALGORITHM_SIZE_HPP
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include<type_traits>
namespace srook{
inline namespace mpl{
inline namespace v1{
namespace detail{

template<class>
struct size_impl;

template<auto... v>
struct size_impl<any_pack<v...>> : std::integral_constant<std::size_t,sizeof...(v)>{};

template<class AnyPack>
static constexpr std::size_t size = size_impl<AnyPack>::value;

} // namespace detail
} // inline namespace v1
} // inline namespace mpl
} // namespace srook

#endif
