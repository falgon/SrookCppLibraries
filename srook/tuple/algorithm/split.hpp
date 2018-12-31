// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_SPLIT_HPP
#define INCLUDED_SROOK_TUPLE_SPLIT_HPP
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/libraries/type_traits/index_sequence.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/utility/declval.hpp>
#include <srook/utility/forward.hpp>
#include <srook/utility/move.hpp>
#include <tuple>
#include <type_traits>

namespace srook {
namespace tuple {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class... Tpl, std::size_t... v>
constexpr auto split_first_impl(const std::tuple<Tpl...>& tp, SROOK_INDEX_SEQUENCE<v...>) SROOK_NOEXCEPT(std::make_tuple(std::get<v>(tp)...))
-> decltype(std::make_tuple(std::get<v>(tp)...))
{
    return std::make_tuple(std::get<v>(tp)...);
}

struct Apply_Split {
    struct invoker {
        template <class... Ts, std::size_t n, std::size_t index, class... Args>
        static SROOK_CONSTEXPR std::tuple<Args...>
        apply(const std::tuple<Ts...>&, std::integral_constant<std::size_t, n>, std::integral_constant<std::size_t, index>, Args&&... args)
        {
            return std::make_tuple(srook::forward<Args>(args)...);
        }
    };

    struct applyer {
        template <class... Ts, std::size_t n, std::size_t index, class... Args>
        static SROOK_CONSTEXPR std::tuple<Args...>
        apply(const std::tuple<Ts...>& t, std::integral_constant<std::size_t, n>, std::integral_constant<std::size_t, index>, Args&&... args)
        {
            return Apply_Split::apply(t, std::integral_constant<std::size_t, n - 1>(), std::integral_constant<std::size_t, index - 1>(), std::get<index>(t), srook::forward<Args>(args)...);
        }
    };

    template <class... Ts, std::size_t n, std::size_t index, class... Args>
    static SROOK_CONSTEXPR std::tuple<Args...>
    apply(const std::tuple<Ts...>& t, std::integral_constant<std::size_t, n> integral_cons, std::integral_constant<std::size_t, index> in, Args&&... args)
    {
        return typename conditional<n == 0, invoker, applyer>::type::apply(t, srook::move(integral_cons), srook::move(in), srook::forward<Args>(args)...);
    }
};

template <std::size_t index, class... Tpl>
constexpr auto split_last_impl(const std::tuple<Tpl...>& tpl) SROOK_NOEXCEPT(Apply_Split::apply(tpl, declval<std::integral_constant<std::size_t, std::tuple_size<std::tuple<Tpl...> >::value - index> >(), declval<std::integral_constant<std::size_t, std::tuple_size<std::tuple<Tpl...> >::value - 1> >()))
    -> decltype(Apply_Split::apply(tpl, declval<std::integral_constant<std::size_t, std::tuple_size<std::tuple<Tpl...> >::value - index> >(), declval<std::integral_constant<std::size_t, std::tuple_size<std::tuple<Tpl...> >::value - 1> >()))
{
    return Apply_Split::apply(
        tpl,
        std::integral_constant<std::size_t, std::tuple_size<std::tuple<Tpl...> >::value - index>(),
        std::integral_constant<std::size_t, std::tuple_size<std::tuple<Tpl...> >::value - 1>());
}

} // namespace detail

template <std::size_t index, class... Tpl>
constexpr auto split_first(const std::tuple<Tpl...>& tpl)
    SROOK_NOEXCEPT(detail::split_first_impl(tpl, declval<SROOK_MAKE_INDEX_SEQUENCE(index)>()))
        -> decltype(detail::split_first_impl(tpl, declval<SROOK_MAKE_INDEX_SEQUENCE(index)>()))
{
    return detail::split_first_impl(tpl, SROOK_MAKE_INDEX_SEQUENCE(index)());
}

template <std::size_t index, class... Tpl>
constexpr auto split_last(const std::tuple<Tpl...>& tpl) SROOK_NOEXCEPT(detail::split_last_impl<index>(tpl))
    -> decltype(detail::split_last_impl<index>(tpl))
{
    return detail::split_last_impl<index>(tpl);
}

template <std::size_t index, class... Tpl>
constexpr auto split(const std::tuple<Tpl...>& tp)
    SROOK_NOEXCEPT(std::make_pair(split_first<index>(tp), split_last<index>(tp)))
        -> decltype(std::make_pair(split_first<index>(tp), split_last<index>(tp)))
{
    return std::make_pair(split_first<index>(tp), split_last<index>(tp));
}

SROOK_INLINE_NAMESPACE_END
} // namespace tuple
} // namespace srook

#endif
