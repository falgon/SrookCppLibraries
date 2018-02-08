// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_BIND_HPP
#define INCLUDED_SROOK_TMPL_VT_BIND_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/apply.hpp>
#include <srook/tmpl/vt/at.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/filter.hpp>
#include <srook/tmpl/vt/not_fn.hpp>
#include <srook/tmpl/vt/insert_at.hpp>
#include <srook/mpl/constant_sequence/algorithm/concat.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/preprocessor/detail/iterate_def.hpp>
#include <srook/utility/enable_copy_move.hpp>
#include <srook/utility/integer_sequence.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class>
struct is_placeholders : SROOK_FALSE_TYPE {};

namespace placeholders {

#define SROOK_TMPL_VT_PLACEHOLDERS_DEFINE(X)\
    struct _##X : enable_copy_move<false, false, false, false, _##X>, integral_constant<std::size_t, X> {};
    SROOK_PP_ITERATE(SROOK_TMPL_VT_PLACEHOLDERS_DEFINE, 32)
#undef SROOK_TMPL_VT_PLACEHOLDERS_DEFINE

} // namespace placeholders

#define SROOK_TMPL_VT_IS_PLACEHOLDERS_DEFINE(X)\
    template <>\
    struct is_placeholders<srook::tmpl::vt::placeholders::_##X> : SROOK_TRUE_TYPE {};
    SROOK_PP_ITERATE(SROOK_TMPL_VT_IS_PLACEHOLDERS_DEFINE, 32)
#undef SROOK_TMPL_VT_IS_PLACEHOLDERS_DEFINE

namespace detail {

template <bool, class, std::size_t>
struct placeholders_instance 
    : type_constant<integer_sequence<std::size_t>> {};
template <class T, std::size_t x>
struct placeholders_instance<true, T, x>
    : type_constant<integer_sequence<std::size_t, T::value - 1, x>> {};

template <std::size_t, class...>
struct placeholders_indexes_impl;

template <std::size_t x, class X, class... Xs>
struct placeholders_indexes_impl<x, X, Xs...> 
    : srook::constant_sequence::concat<
        SROOK_DEDUCED_TYPENAME placeholders_instance<is_placeholders<X>::value, X, x>::type,
        SROOK_DEDUCED_TYPENAME placeholders_indexes_impl<x + 1, Xs...>::type
      > {};

template <std::size_t x>
struct placeholders_indexes_impl<x>
    : type_constant<integer_sequence<std::size_t>> {};

template <class... Xs>
struct placeholders_indexes : placeholders_indexes_impl<0, Xs...> {};

template <class, template <class...> class, class...>
struct bind_impl;

template <template <class...> class F, class... Xs>
struct bind_impl<integer_sequence<std::size_t>, F, Xs...> {
protected:
    template <class... U>
    struct type : bool_constant<F<Xs..., U...>::value> {};
};

template <std::size_t x, class T>
struct bind_pairlist 
    : integral_constant<std::size_t, x>, type_constant<T> {};

template <class, class...>
struct make_bind_pairlist;

template <std::size_t x, std::size_t y, std::size_t... xs, class... Xs>
struct make_bind_pairlist<integer_sequence<std::size_t, x, y, xs...>, Xs...>
    : concat<
        bind_pairlist<y, SROOK_DEDUCED_TYPENAME at<x, Xs...>::type>,
        SROOK_DEDUCED_TYPENAME make_bind_pairlist<
            integer_sequence<std::size_t, xs...>,
            Xs...
        >::type
      > {};

template <class X, class... Xs>
struct make_bind_pairlist<integer_sequence<std::size_t>, X, Xs...>
    : type_constant<packer<>> {};

template <class, class>
struct make_arguments;

template <class X, class... Xs, std::size_t x, class T, class... Bds>
struct make_arguments<packer<X, Xs...>, packer<bind_pairlist<x, T>, Bds...>>
    : make_arguments<
        SROOK_DEDUCED_TYPENAME srook::tmpl::vt::insert_at<x, T, X, Xs...>::type,
        packer<Bds...>
      > {};
    
template <class... Xs>
struct make_arguments<packer<Xs...>, packer<>>
    : type_constant<packer<Xs...>> {};

template <template <class...> class, class, class>
struct splited_invoke;

template <template <class...> class F, class... Xs, class... Ys>
struct splited_invoke<F, packer<Xs...>, packer<Ys...>> {
private:
    typedef SROOK_DEDUCED_TYPENAME placeholders_indexes<Xs...>::type phi_type;
    typedef SROOK_DEDUCED_TYPENAME make_bind_pairlist<phi_type, Ys...>::type bind_pairlist;
    typedef SROOK_DEDUCED_TYPENAME filter<not_fn<is_placeholders>::template type, Xs...>::type filterd;
    typedef SROOK_DEDUCED_TYPENAME make_arguments<filterd, bind_pairlist>::type arguments;
public:
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool value = srook::tmpl::vt::apply<F, arguments>::value;
};

template <std::size_t x, std::size_t... xs, template <class...> class F, class... Xs>
struct bind_impl<integer_sequence<std::size_t, x, xs...>, F, Xs...> {
protected:
    template <class... U>
    struct type 
        : splited_invoke<F, packer<Xs...>, packer<U...>> {}; 
};

} // namespace detail

template <template <class...> class F, class... Xs>
struct bind 
    : detail::bind_impl<SROOK_DEDUCED_TYPENAME detail::placeholders_indexes<Xs...>::type, F, Xs...> {
private:
    typedef 
        detail::bind_impl<SROOK_DEDUCED_TYPENAME detail::placeholders_indexes<Xs...>::type, F, Xs...> 
    base_type;
public:
    using base_type::type;
};

// qsort は右側に入れるため第二引数をバインド

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
