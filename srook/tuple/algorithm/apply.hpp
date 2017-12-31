// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_ALGORITHM_APPLY_HPP
#define INCLUDED_SROOK_TUPLE_ALGORITHM_APPLY_HPP
#include <tuple>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/functional/invoke.hpp>
#include <srook/type_traits/invoke_result.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/type_traits/concepts/cxx17/invoke.hpp>
#include <srook/tuple/algorithm/apply.hpp>
#include <srook/utility/forward.hpp>
#include <srook/utility/index_sequence.hpp>
#include <srook/config/feature/constexpr.hpp>

namespace srook {
namespace tuple {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class F, class Tuple, std::size_t... I>
SROOK_CONSTEXPR auto apply_impl(F&& f, Tuple&& t, index_sequence<I...>)
-> typename invoke_result<F, decltype(std::get<I>(t))...>::type 
{
	return invoke(srook::forward<F>(f), std::get<I>(srook::forward<Tuple>(t))...);
}

} // namespace detail

template <class F, class Tuple>
SROOK_CONSTEXPR auto apply(F&& f, Tuple&& t)
-> decltype(
		detail::apply_impl(
			declval<F>(), 
			declval<Tuple>(), 
			typename make_index_sequence_type<std::tuple_size<typename decay<Tuple>::type>::value>::type()
		)
	)
{
    return detail::apply_impl(
        srook::forward<F>(f), srook::forward<Tuple>(t),
        typename make_index_sequence_type<std::tuple_size<typename decay<Tuple>::type>::value>::type()
	);
}

SROOK_INLINE_NAMESPACE_END
} // namespace tuple

using tuple::apply;

} // namespace srook

#endif
