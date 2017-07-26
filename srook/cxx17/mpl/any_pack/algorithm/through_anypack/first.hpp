#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ALGORITHM_THROUGH_ANY_PACK_FIRST_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ALGORITHM_THROUGH_ANY_PACK_FIRST_HPP
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include<srook/cxx17/mpl/any_pack/algorithm/first.hpp>
namespace srook{
inline namespace mpl{
namespace through{
namespace detail{

template<class>
struct first;

template<auto... v>
struct first<any_pack<v...>>{
	static constexpr decltype(auto) value = srook::detail::first_v<v...>;
};

} // namespace detail

template<class Anypack>
static constexpr decltype(auto) first_v = detail::first<Anypack>::value;

} // namespace through
} // inline namespace mpl
} // namespace srook

#endif
