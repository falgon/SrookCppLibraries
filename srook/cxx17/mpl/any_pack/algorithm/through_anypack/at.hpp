#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ALGORITHM_THROUGH_ANY_PACK_AT_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ALGORITHM_THROUGH_ANY_PACK_AT_HPP
#include <srook/cxx17/mpl/any_pack/algorithm/at.hpp>
#include <srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
namespace srook {
inline namespace mpl {
namespace through {
namespace detail {

template <std::size_t, class>
struct at;

template <std::size_t i, auto... v>
struct at<i, any_pack<v...>> {
    static constexpr decltype(auto) value = srook::detail::at_v<i, v...>;
};

} // namespace detail

template <std::size_t i, class Anypack>
static constexpr decltype(auto) at_v = detail::at<i, Anypack>::value;

} // namespace through
} // namespace mpl
} // namespace srook

#endif
