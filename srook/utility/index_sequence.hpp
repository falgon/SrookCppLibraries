#ifndef INCLUDED_SROOK_UTILITY_INDEX_SEQUENCE_HPP
#define INCLUDED_SROOK_UTILITY_INDEX_SEQUENCE_HPP
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/utility/integer_sequence.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/noexcept_detection.hpp>

namespace srook{
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPP_ALIAS_TEMPLATES

template <std::size_t... v>
using index_sequence = integer_sequence<std::size_t, v...>;

#else

template <std::size_t... v>
struct index_sequence : integer_sequence<std::size_t, v...> {};

#endif

namespace detail {

template <std::size_t, class>
struct make_index_sequence_impl;

template <std::size_t n, std::size_t... v>
struct make_index_sequence_impl<n, index_sequence<v...>> {
	typedef typename make_index_sequence_impl<n-1, index_sequence<n-1, v...>>::type type;
};

template <std::size_t... v>
struct make_index_sequence_impl<0, index_sequence<v...>> {
	typedef index_sequence<v...> type;
};

} // namespace detail

template <std::size_t n
#if (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
, class Seq = index_sequence<>
#endif
>
struct make_index_sequence_type : detail::make_index_sequence_impl<n,
#if (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
	Seq
#else
	index_sequence<>
#endif
	> {};

SROOK_INLINE_NAMESPACE_END
} // namespace utility

using utility::index_sequence;
using utility::make_index_sequence_type;

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t n, class Seq = index_sequence<>>
using make_index_sequence = typename make_index_sequence_type<n, Seq>::type;
#endif

} // namespace srook

#endif
#endif
