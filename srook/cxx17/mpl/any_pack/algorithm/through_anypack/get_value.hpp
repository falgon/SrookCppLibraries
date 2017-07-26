#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ALGORITHM_THROUGH_GET_VALUE_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ALGORITHM_THROUGH_GET_VALUE_HPP
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
namespace srook{
inline namespace mpl{
namespace through{
namespace detail{

template<class S>
struct get_value_impl{
	static constexpr decltype(auto) value = S::value;
};

} // namespace detail

template<class Anypack>
static constexpr decltype(auto) get_value = through::detail::get_value_impl<Anypack>::value;

} // namespace through
} // inline namespace mpl
} // namespace srook

#endif
