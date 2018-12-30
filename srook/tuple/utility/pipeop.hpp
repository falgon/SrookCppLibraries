// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_UTILITY_PIPEOP_HPP
#define INCLUDED_SROOK_TUPLE_UTILITY_PIPEOP_HPP

#include <srook/tuple/utility/detail/utils.hpp>
#include <srook/type_traits/is_tuple.hpp>

SROOK_NESTED_NAMESPACE(srook, tuple, utility) {
SROOK_INLINE_NAMESPACE(v1)

namespace pipeop {
namespace reverse {

template <class F, class Tuple, 
SROOK_REQUIRES(type_traits::detail::Land<is_tuple<SROOK_DEDUCED_TYPENAME decay<Tuple>::type>, is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, Tuple&&>>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME invoke_result<SROOK_DEDUCED_TYPENAME decay<F>::type, Tuple&&>::type
operator|(F&& f, Tuple&& tpl) 
SROOK_NOEXCEPT(is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, Tuple&&>::value)
{
    return srook::invoke(srook::forward<F>(f), srook::forward<Tuple>(tpl));
}

} // namespace reverse

SROOK_INLINE_NAMESPACE(normal)

template <class F, class Tuple, 
SROOK_REQUIRES(type_traits::detail::Land<is_tuple<SROOK_DEDUCED_TYPENAME decay<Tuple>::type>, is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, Tuple&&>>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME invoke_result<SROOK_DEDUCED_TYPENAME decay<F>::type, Tuple&&>::type
operator|(Tuple&& tpl, F&& f) 
SROOK_NOEXCEPT(is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, Tuple&&>::value)
{
    return srook::invoke(srook::forward<F>(f), srook::forward<Tuple>(tpl));
}

SROOK_INLINE_NAMESPACE_END
} // namespace pipeop

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(utility, tuple, srook)
#endif
