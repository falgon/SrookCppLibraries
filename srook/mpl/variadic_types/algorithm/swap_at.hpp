// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_SWAP_AT_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_SWAP_AT_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/algorithm/concat.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class, class, std::size_t, class, class>
struct SwapAt;
template <class LH, class... LT, class RH, class... RT, std::size_t n, class LHeads, class RHeads>
struct SwapAt<pack<LH, LT...>, pack<RH, RT...>, n, LHeads, RHeads> {
    using L_type = typename SwapAt<pack<LT...>, pack<RT...>, n - 1, Concat_t<LH, LHeads>, Concat_t<RH, RHeads>>::L_type;
    using R_type = typename SwapAt<pack<LT...>, pack<RT...>, n - 1, Concat_t<LH, LHeads>, Concat_t<RH, RHeads>>::R_type;
};
template <class LT, class... L, class RT, class... R, class LHeads, class RHeads>
struct SwapAt<pack<LT, L...>, pack<RT, R...>, 0, LHeads, RHeads> {
    using L_type = Concat_t<LHeads, pack<RT, L...>>;
    using R_type = Concat_t<RHeads, pack<LT, R...>>;
};
} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::SwapAt;

template <class LPack, class RPack, std::size_t IndexTarget>
struct SwapAt_L_type {
    using type = typename variadic_types::detail::SwapAt<LPack, RPack, IndexTarget, pack<>, pack<>>::L_type;
};
template <class LPack, class RPack, std::size_t IndexTarget>
struct SwapAt_R_type {
    using type = typename variadic_types::detail::SwapAt<LPack, RPack, IndexTarget, pack<>, pack<>>::R_type;
};

#if SROOK_CPP_ALIAS_TEMPLATES

template <class LPack, class RPack, std::size_t IndexTarget>
using SwapAt_L = typename variadic_types::detail::SwapAt<LPack, RPack, IndexTarget, pack<>, pack<>>::L_type;
template <class LPack, class RPack, std::size_t IndexTarget>
using SwapAt_R = typename variadic_types::detail::SwapAt<LPack, RPack, IndexTarget, pack<>, pack<>>::R_type;

#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
