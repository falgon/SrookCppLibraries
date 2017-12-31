// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_SWAP_AT_SPECIFIED_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_SWAP_AT_SPECIFIED_HPP
#include <cstddef>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/algorithm/at.hpp>
#include <srook/mpl/variadic_types/algorithm/concat.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class, std::size_t, class, std::size_t, class, class, std::size_t, std::size_t>
struct SwapAt_Specified_L_t;

template <class, std::size_t, class, std::size_t, class, class, std::size_t, std::size_t>
struct SwapAt_Specified_R_t;

template <
    class LH, class... LT, std::size_t IL,
    class... R, std::size_t IR,
    class LHeads, class RHeads,
    std::size_t CORE_IL, std::size_t CORE_IR>
struct SwapAt_Specified_L_t<
    pack<LH, LT...>, IL,
    pack<R...>, IR,
    LHeads, RHeads,
    CORE_IL, CORE_IR> {
    using L_type =
	typename SwapAt_Specified_L_t<
	    pack<LT...>, IL - 1,
	    pack<R...>, IR,
	    Concat_t<LH, LHeads>, pack<R...>,
	    CORE_IL, CORE_IR>::L_type;
};

template <
    class... L, std::size_t IL,
    class RH, class... RT, std::size_t IR,
    class LHeads, class RHeads,
    std::size_t CORE_IL, std::size_t CORE_IR>
struct SwapAt_Specified_R_t<
    pack<L...>, IL,
    pack<RH, RT...>, IR,
    LHeads, RHeads,
    CORE_IL, CORE_IR> {
    using R_type =
	typename SwapAt_Specified_R_t<
	    pack<L...>, IL,
	    pack<RT...>, IR - 1,
	    pack<L...>, typename Concat<RH, RHeads>::type,
	    CORE_IL, CORE_IR>::R_type;
};

template <
    class LH, class... LT,
    class... R, std::size_t IR,
    class LHeads, class RHeads,
    std::size_t CORE_IL, std::size_t CORE_IR>
struct SwapAt_Specified_L_t<
    pack<LH, LT...>, 0,
    pack<R...>, IR,
    LHeads, RHeads,
    CORE_IL, CORE_IR> {
    using L_type =
	typename Concat<
	    typename Concat<
		LHeads,
		typename At<CORE_IR, pack<R...>>::type>::type,
	    LT...>::type;
};
template <
    class... L, std::size_t IL,
    class RH, class... RT,
    class LHeads, class RHeads,
    std::size_t CORE_IL, std::size_t CORE_IR>
struct SwapAt_Specified_R_t<
    pack<L...>, IL,
    pack<RH, RT...>, 0,
    LHeads, RHeads,
    CORE_IL, CORE_IR> {
    using R_type =
	typename Concat<
	    typename Concat<
		RHeads,
		typename At<CORE_IL, pack<L...>>::type>::type,
	    RT...>::type;
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::SwapAt_Specified_L_t;
using variadic_types::detail::SwapAt_Specified_R_t;

template <class LPack, std::size_t IL, class RPack, std::size_t IR>
struct SwapAt_Specified_L_type {
    using type = typename variadic_types::detail::SwapAt_Specified_L_t<LPack, IL, RPack, IR, pack<>, pack<>, IL, IR>::L_type;
};
template <class LPack, std::size_t IL, class RPack, std::size_t IR>
struct SwapAt_Specified_R_type {
    using type = typename variadic_types::detail::SwapAt_Specified_R_t<LPack, IL, RPack, IR, pack<>, pack<>, IL, IR>::R_type;
};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class LPack, std::size_t IL, class RPack, std::size_t IR>
using SwapAt_Specified_L = typename SwapAt_Specified_L_t<LPack, IL, RPack, IR, pack<>, pack<>, IL, IR>::L_type;
template <class LPack, std::size_t IL, class RPack, std::size_t IR>
using SwapAt_Specified_R = typename SwapAt_Specified_R_t<LPack, IL, RPack, IR, pack<>, pack<>, IL, IR>::R_type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
