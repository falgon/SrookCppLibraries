#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ALGORITHM_THROUGH_ANY_PACK_PARTIAL_HEAD_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ALGORITHM_THROUGH_ANY_PACK_PARTIAL_HEAD_HPP
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include<srook/cxx17/mpl/any_pack/algorithm/partial_head.hpp>
namespace srook{
inline namespace mpl{
namespace through{
namespace detail{

template<std::size_t,class>
struct partial_head;

template<std::size_t index,auto... v>
struct partial_head<index,any_pack<v...>>{
	using type = srook::mpl::v1::detail::partial_head_t<index,v...>;
};

} // namespace detail

template<std::size_t index,class Anypack>
using partial_head_t = typename detail::partial_head<index,Anypack>::type;

} // namespace through
} // inline namespace mpl
} // namespace srook

#endif
