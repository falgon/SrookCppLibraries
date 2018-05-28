// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_OPIONAL_APPLICATIVE_HPP
#define INCLUDED_SROOK_OPIONAL_APPLICATIVE_HPP
#include <srook/type_traits/is_optional.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPP_ALIAS_TEMPLATES
#include <srook/type_traits/decay.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/is_nothrow_invocable.hpp>
#include <srook/functional/invoke.hpp>
#include <srook/tuple/algorithm/apply.hpp>
#include <srook/utility/move.hpp>

SROOK_NESTED_NAMESPACE(srook, optionally) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

#if !SROOK_CPP_FOLD_EXPRESSIONS
template <class B, SROOK_REQUIRES(is_same<SROOK_DEDUCED_TYPENAME decay<B>::type, bool>::value)>
SROOK_CONSTEXPR SROOK_FORCE_INLINE B&& all_true(B&& b) SROOK_NOEXCEPT_TRUE { return srook::forward<B>(b); }

template <class B1, class B2, class... Bs, 
SROOK_REQUIRES(
    type_traits::detail::Land<
        is_same<SROOK_DEDUCED_TYPENAME decay<B1>::type, bool>,
        is_same<SROOK_DEDUCED_TYPENAME decay<B2>::type, bool>,
        is_same<bool, SROOK_DEDUCED_TYPENAME decay<Bs>::type>...
    >::value
)>
SROOK_CONSTEXPR bool all_true(B1&& b1, B2&& b2, Bs&&... bs) SROOK_NOEXCEPT_TRUE
{
    return b1 && all_true(srook::forward<B2>(b2), srook::forward<Bs>(bs)...);
}
#endif

template <template <class, bool, bool> class>
struct is_basic_optional_payload : SROOK_FALSE_TYPE {};

template <>
struct is_basic_optional_payload<optional_payload> : SROOK_TRUE_TYPE {};

template <class>
struct take_payload;

template <class T, template <class, bool, bool> class Payload>
struct take_payload<optional<T, Payload>> {
    template <class U, bool b1, bool b2>
    using type = Payload<U, b1, b2>;
};

template <class... Opts>
struct optional_payload_common_type 
    : conditional<
        type_traits::detail::Land<is_basic_optional_payload<take_payload<Opts>::template type>...>::value,
        take_payload<optional<char, optional_payload>>,     // dummy value_type
        take_payload<optional<char, safe_optional_payload>> // ditto
      > {};

template <bool>
struct make_optional_from_common_payload {
    template <class T>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR optional<T, optional_payload> operator()(T&& value) const
    SROOK_NOEXCEPT(is_nothrow_constructible<optional<T, optional_payload>, T&&>::value)
    {
        return srook::make_optional(srook::forward<T>(value));
    }
};

template <>
struct make_optional_from_common_payload<false> {
    template <class T>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR optional<T, safe_optional_payload> operator()(T&& value) const
    SROOK_NOEXCEPT(is_nothrow_constructible<optional<T, safe_optional_payload>, T&&>::value)
    {
        return srook::make_safe_optional(srook::forward<T>(value));
    }
};

template <class... Opts>
using make_optional_common_type = 
detail::make_optional_from_common_payload<
    type_traits::detail::Land<
        is_basic_optional_payload<take_payload<SROOK_DEDUCED_TYPENAME decay<Opts>::type>::template type>...
    >::value
>;

} // namespace detail

template <class F, class... Ts,
SROOK_REQUIRES(
    type_traits::detail::Land<
        is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Ts>::type::value_type...>,
        is_optional<SROOK_DEDUCED_TYPENAME decay<Ts>::type>...
    >::value
)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
invoke_result<
    detail::make_optional_common_type<Ts...>,
    SROOK_DEDUCED_TYPENAME invoke_result<F&&, SROOK_DEDUCED_TYPENAME decay<Ts>::type::value_type...>::type
>::type
applicative(F&& f, Ts&&... ts)
SROOK_NOEXCEPT(is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Ts>::type::value_type...>::value)
{
    return
#if SROOK_CPP_FOLD_EXPRESSIONS
    (ts && ...)
#else
    detail::all_true(bool(ts)...)
#endif
    ? detail::make_optional_common_type<Ts...>()(srook::invoke(srook::forward<F>(f), srook::forward<Ts>(*ts)...)) : srook::nullopt;
}

#if !SROOK_CPP_LAMBDAS
namespace detail {

template <class ResultType, bool is_noexcept>
struct nolambda {
    template <class F, class... Ts>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR ResultType 
    operator()(F&& f, Ts&&... ts) SROOK_NOEXCEPT(is_noexcept) { return applicative(srook::forward<F>(f), srook::forward<Ts>(ts)...); }
};

} // namespace detail 
#endif

template <class F, class... Ts,
SROOK_REQUIRES(
    type_traits::detail::Land<
        is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Ts>::type::value_type...>,
        is_optional<SROOK_DEDUCED_TYPENAME decay<Ts>::type>...
    >::value
)>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR SROOK_DEDUCED_TYPENAME
invoke_result<
    detail::make_optional_common_type<Ts...>,
    SROOK_DEDUCED_TYPENAME invoke_result<F&&, SROOK_DEDUCED_TYPENAME decay<Ts>::type::value_type...>::type
>::type
applicative(F&& f, std::tuple<Ts...> tp)
SROOK_NOEXCEPT(is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Ts>::type::value_type...>::value)
{
    typedef SROOK_DEDUCED_TYPENAME invoke_result<
        detail::make_optional_common_type<Ts...>, 
        SROOK_DEDUCED_TYPENAME invoke_result<F&&, SROOK_DEDUCED_TYPENAME decay<Ts>::type::value_type...>::type
    >::type result_type;

    SROOK_CONSTEXPR_OR_CONST bool is_noexcept = is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Ts>::type::value_type...>::value;
#if SROOK_CPP_LAMBDAS
    auto l = [](auto&& ff, auto&&... ts) SROOK_CXX17_CONSTEXPR noexcept(is_noexcept) -> result_type {
        return applicative(srook::forward<SROOK_DECLTYPE(ff)>(ff), srook::forward<SROOK_DECLTYPE(ts)>(ts)...); 
    };
#else
    detail::nolambda<result_type, is_noexcept> l;
#endif
    return srook::apply(srook::move(l), std::tuple_cat(std::forward_as_tuple(srook::forward<F>(f)), srook::move(tp)));
}

namespace applicative_operators {

template <class F, class Optional,
SROOK_REQUIRES(
    type_traits::detail::Land<
        is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Optional>::type::value_type>,
        is_optional<SROOK_DEDUCED_TYPENAME decay<Optional>::type>
    >::value
)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
invoke_result<
    detail::make_optional_common_type<Optional>,
    SROOK_DEDUCED_TYPENAME invoke_result<F&&, SROOK_DEDUCED_TYPENAME decay<Optional>::type::value_type>::type
>::type
operator&(F&& f, Optional&& opt)
SROOK_NOEXCEPT(is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Optional>::type::value_type>::value)
{
    return srook::optionally::applicative(srook::forward<F>(f), srook::forward<Optional>(opt));
}

// <$>
template <class F, class... Optionals,
SROOK_REQUIRES(
    type_traits::detail::Land<
        is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Optionals>::type::value_type...>,
        is_optional<SROOK_DEDUCED_TYPENAME decay<Optionals>::type>...
    >::value
)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
invoke_result<
    detail::make_optional_common_type<Optionals...>,
    SROOK_DEDUCED_TYPENAME invoke_result<F&&, SROOK_DEDUCED_TYPENAME decay<Optionals>::type::value_type...>::type
>::type
operator&(F&& f, std::tuple<Optionals...> tp)
SROOK_NOEXCEPT(is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Optionals>::type::value_type...>::value)
{
    return srook::optionally::applicative(srook::forward<F>(f), srook::move(tp));
}

// <*>
template <class Optional, SROOK_REQUIRES(is_optional<SROOK_DEDUCED_TYPENAME decay<Optional>::type>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR std::tuple<Optional&&, Optional&&>
operator*(Optional&& lhs, Optional&& rhs) SROOK_NOEXCEPT_TRUE
{
    return std::forward_as_tuple(srook::forward<Optional>(lhs), srook::forward<Optional>(rhs));
}

// <*>
template <class Optional, class... Opts,
SROOK_REQUIRES(type_traits::detail::Land<is_optional<SROOK_DEDUCED_TYPENAME decay<Optional>::type>, is_optional<SROOK_DEDUCED_TYPENAME decay<Opts>::type>...>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR std::tuple<Optional&&, Opts...>
operator*(Optional&& lhs, std::tuple<Opts...> tp) SROOK_NOEXCEPT_TRUE
{
    return std::tuple_cat(std::forward_as_tuple(srook::forward<Optional>(lhs)), srook::move(tp));
}

// <*>
template <class Optional, class... Opts,
SROOK_REQUIRES(type_traits::detail::Land<is_optional<SROOK_DEDUCED_TYPENAME decay<Optional>::type>, is_optional<SROOK_DEDUCED_TYPENAME decay<Opts>::type>...>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR std::tuple<Opts..., Optional&&>
operator*(std::tuple<Opts...> tp, Optional&& rhs) SROOK_NOEXCEPT_TRUE
{
    return std::tuple_cat(srook::move(tp), std::forward_as_tuple(srook::forward<Optional>(rhs)));
}

} // namespace applicative_operators

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(optionally, srook)

namespace srook {

using srook::optionally::applicative;

} // namespace srook

#endif
#endif
