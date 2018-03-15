// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_PARTIAL_TAIL_HPP
#define INCLUDED_SROOK_TMPL_VT_PARTIAL_TAIL_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/utility/index_sequence.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

#if 0
template <std::size_t k, class... Ts>
struct partial_tail 
    : public type_constant<SROOK_DEDUCED_TYPENAME detail::PartialTail<k, Ts...>::type::rebind_packer> {};

template <std::size_t k, class... Ts>
struct partial_tail<k, packer<Ts...>> : public partial_tail<k, Ts...> {};

#else

namespace detail {

template <class> struct partial_tail_impl;

template <std::size_t... x>
struct partial_tail_impl<srook::utility::index_sequence<x...> > {
    template <class... Ts>
    static packer<Ts...> 
    get(SROOK_DEDUCED_TYPENAME voider<integral_constant<std::size_t, x> >::type*..., Ts*..., ...);
};

} // namespace detail

template <std::size_t k, class... Ts>
struct partial_tail
    : type_constant<
        SROOK_DECLTYPE(
            detail::partial_tail_impl<
                SROOK_DEDUCED_TYPENAME make_index_sequence_type<k + 1>::type
            >::get(SROOK_DEDUCED_TYPENAME add_pointer<Ts>::type()...)
        )
    > {};

template <std::size_t k, class... Ts>
struct partial_tail<k, packer<Ts...>> : partial_tail<k, Ts...> {};

#endif

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t k, class... Ts>
using partial_tail_t = SROOK_DEDUCED_TYPENAME partial_tail<k, Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
