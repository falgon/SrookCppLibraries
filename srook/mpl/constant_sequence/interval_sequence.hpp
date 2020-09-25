// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_INTERVAL_SEQUENCE_IMPL
#define INCLUDED_SROOK_INTERVAL_SEQUENCE_IMPL
#include <memory>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/mpl/constant_sequence/algorithm/concat.hpp>
#include <utility>

namespace srook {
inline namespace mpl {
inline namespace v1 {
namespace detail {
namespace interval_sequence {

struct plus {
    template <class L, class R>
    static constexpr decltype(std::declval<L>() + std::declval<R>()) apply(L a, R b) noexcept
    {
	return a + b;
    }
};
struct minus {
    template <class L, class R>
    static constexpr decltype(std::declval<L>() - std::declval<R>()) apply(L a, R b) noexcept
    {
	return a - b;
    }
};
struct multiply {
    template <class L, class R>
    static constexpr decltype(std::declval<L>() * std::declval<R>()) apply(L a, R b) noexcept
    {
	return a * b;
    }
};
struct division {
    template <class L, class R>
    static constexpr decltype(std::declval<L>() / std::declval<R>()) apply(L a, R b) noexcept
    {
	return b ? a / b : 0;
    }
};

} // namespace interval_sequence

template <class IntervalOperation, std::size_t start_value, std::size_t intervalue, std::size_t size>
struct make_interval_sequence_impl {
    using type =
	::srook::constant_sequence::concat_t<
	    std::index_sequence<start_value>,
	    typename make_interval_sequence_impl<IntervalOperation, IntervalOperation::apply(start_value, intervalue), intervalue, size - 1>::type>;
};
template <class IntervalOperation, std::size_t start_value, std::size_t intervalue>
struct make_interval_sequence_impl<IntervalOperation, start_value, intervalue, 0> {
    using type = std::index_sequence<>;
};
} // namespace detail

using namespace detail::interval_sequence;

template <class IntervalOperation, std::size_t start_value, std::size_t intervalue, std::size_t size>
struct make_interval_sequence_type {
    typedef typename detail::make_interval_sequence_impl<IntervalOperation, start_value, intervalue, size>::type type;
};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class IntervalOperation, std::size_t start_value, std::size_t intervalue, std::size_t size>
using make_interval_sequence = typename detail::make_interval_sequence_impl<IntervalOperation, start_value, intervalue, size>::type;
#endif

} // namespace v1
} // namespace mpl
} // namespace srook
#endif
