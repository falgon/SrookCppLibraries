#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ALGORITHM_THROUGH_ANY_PACK_PARTIAL_TAIL_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ALGORITHM_THROUGH_ANY_PACK_PARTIAL_TAIL_HPP
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include<srook/cxx17/mpl/any_pack/algorithm/partial_tail.hpp>
namespace srook{
inline namespace mpl{
namespace through{
namespace detail{

template<std::size_t,class>
struct partial_tail;

template<std::size_t index,auto... v>
struct partial_tail<index,any_pack<v...>>{
	using type = srook::detail::partial_tail_t<index,v...>;
};

} // namespace detail

template<std::size_t index,class Anypack>
using partial_tail_t = typename detail::partial_tail<index,Anypack>::type;

} // namespace through
} // inline namespace mpl
} // namespace srook

#endif
