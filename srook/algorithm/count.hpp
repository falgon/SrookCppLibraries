// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_COUNT_HPP
#define INCLUDED_SROOK_ALGORITHM_COUNT_HPP
#include <algorithm>
#include <srook/config/require.hpp>
#include <srook/tuple/algorithm/filter_type.hpp>
#include <srook/type_traits/has_iterator.hpp>
#include <srook/type_traits/is_callable.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/utility/forward.hpp>

namespace srook {
namespace algorithm {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

struct Apply_Counter {
    struct invoker {
	template <class... Ts, class Target, std::size_t index, class... Args>
	static std::size_t constexpr apply(const std::tuple<Ts...> &, Target &&, std::integral_constant<std::size_t, index>, std::size_t counter, Args &&...)
	{
	    return counter;
	}
    };

    struct unpacker {
	template <class... Ts, class Target, std::size_t index, class... Args>
	static std::size_t constexpr apply(const std::tuple<Ts...> &tpl, Target &&t, std::integral_constant<std::size_t, index>, std::size_t counter, Args &&... args)
	{
	    if (std::get<index>(tpl) == t) {
		return Apply_Counter::apply(tpl, srook::forward<Target>(t), std::integral_constant<std::size_t, index - 1>(), counter + 1, std::get<index>(tpl), srook::forward<Args>(args)...);
	    } else {
		return Apply_Counter::apply(tpl, srook::forward<Target>(t), std::integral_constant<std::size_t, index - 1>(), counter, std::get<index>(tpl), srook::forward<Args>(args)...);
	    }
	}
    };

    template <class... Ts, class Target, std::size_t index, class... Args>
    static constexpr std::size_t apply(const std::tuple<Ts...> &tpl, Target &&t, std::integral_constant<std::size_t, index> ic, std::size_t counter, Args &&... args)
    {
	return typename conditional<std::tuple_size<std::tuple<Ts...>>::value == sizeof...(args), invoker, unpacker>::type::apply(tpl, srook::forward<Target>(t), std::move(ic), std::move(counter), srook::forward<Args>(args)...);
    }
};

template <class Target_T>
struct counter {
    template <class T>
    using is_same = std::is_same<Target_T, T>;

    template <class... Ts, class Target>
    static constexpr std::size_t count_impl(const std::tuple<Ts...> &tpl, Target &&t)
    {
	return Apply_Counter::apply(
	    tuple::filter_type<is_same>(tpl),
	    srook::forward<Target>(t),
	    std::integral_constant<std::size_t, std::tuple_size<decltype(tuple::filter_type<is_same>(tpl))>::value - 1>(), 0);
    }
};

} // namespace detail

template <class... Ts, class Target>
constexpr std::size_t count(const std::tuple<Ts...> &tp, Target &&t)
{
    return detail::counter<typename decay<Target>::type>::count_impl(tp, srook::forward<Target>(t));
}

template <class Range, class Target, REQUIRES(has_iterator<typename decay<Range>::type>::value)>
constexpr std::size_t count(Range &&r, Target &&target)
{
    return std::count(std::begin(r), std::end(r), srook::forward<Target>(target));
}

template <class Iter, class Target, REQUIRES(!has_iterator<typename decay<Iter>::type>::value)>
constexpr std::size_t count(Iter &&first, Iter &&last, Target &&target)
{
    return std::count(srook::forward<Iter>(first), srook::forward<Iter>(last), srook::forward<Target>(target));
}
SROOK_INLINE_NAMESPACE_END
} // namespace algorithm

using algorithm::count;

} // namespace srook

#endif
