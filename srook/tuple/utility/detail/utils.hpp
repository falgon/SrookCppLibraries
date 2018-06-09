// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_UTILITY_DETAIL_UTILS_HPP
#define INCLUDED_SROOK_TUPLE_UTILITY_DETAIL_UTILS_HPP

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOOK_CPLUSPLUS11_CONSTANT
#include <srook/functional/invoke.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/type_traits/invoke_result.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/is_nothrow_invocable.hpp>
#include <srook/type_traits/is_callable.hpp>
#include <srook/type_traits/is_member_function_pointer.hpp>
#include <srook/type_traits/arguments.hpp>
#include <srook/type_traits/derivation_invoke_result.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tuple/algorithm/apply.hpp>
#include <srook/utility/lambda_wrapper.hpp>
#include <tuple>

SROOK_NESTED_NAMESPACE(srook, tuple, utility) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <bool, class T>
struct wrap_tuple {
    SROOK_STATIC_ASSERT((type_traits::detail::Lnot<is_same<T, T>>::value), "never unreached here");
};

template <class T>
struct wrap_tuple<true, T>
    : srook::tmpl::vt::transfer<std::tuple, T> {};

template <class F>
struct argument_type 
    : arguments_specialized<SROOK_DEDUCED_TYPENAME decay<F>::type, wrap_tuple> {};

template <class F>
struct result_type
    : derivation_invoke_result<SROOK_DEDUCED_TYPENAME decay<F>::type> {};

template <class F>
struct is_noexcept_type 
    : srook::tmpl::vt::transfer<
        is_nothrow_invocable,
        SROOK_DEDUCED_TYPENAME srook::tmpl::vt::concat<
            SROOK_DEDUCED_TYPENAME decay<F>::type, 
            SROOK_DEDUCED_TYPENAME arguments<SROOK_DEDUCED_TYPENAME decay<F>::type>::type
        >::type
    >::type {};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(utility, tuple, srook)
#endif
#endif
