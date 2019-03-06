// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_VECTOR_OPERATION_HPP
#define INCLUDED_SROOK_TUPLE_VECTOR_OPERATION_HPP
#include <algorithm>
#include <functional> // for std::plus,std::minus ...
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/require.hpp>
#include <srook/tuple/algorithm/deprecated/split.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/conjunction.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/type_traits/is_tuple.hpp>
#include <srook/utility/forward.hpp>
#include <srook/utility/move.hpp>
#include <tuple>
#include <type_traits>

namespace srook {
namespace tuple {
namespace numeric {
inline namespace v1 {
namespace detail {

template <std::size_t river_index>
struct tuple_split_adaptor {
    template <class... Ts>
    static SROOK_CONSTEXPR auto apply(const std::tuple<Ts...>& t)
        -> decltype(split<std::tuple_size<std::tuple<Ts...> >::value - river_index>(t).second)
    {
        return split<std::tuple_size<std::tuple<Ts...> >::value - river_index>(t).second;
    }
};

template <>
struct tuple_split_adaptor<0> {
    template <class... Ts>
    static SROOK_CONSTEXPR std::tuple<> apply(const std::tuple<Ts...>&)
    {
        return std::make_tuple();
    }
};

template <bool>
struct tuple_vector_operation_resulter;

template <>
struct tuple_vector_operation_resulter<true> {
    template <template <class> class Operator, class... L_Tuple, class... R_Tuple, std::size_t index, bool rc, class... Args>
    static SROOK_CONSTEXPR std::tuple<L_Tuple..., R_Tuple...>
    apply(const std::tuple<L_Tuple...>&, const std::tuple<R_Tuple...>& r, std::integral_constant<std::size_t, index>, std::integral_constant<bool, rc>, Args&&... args)
    {
        SROOK_CONSTEXPR std::size_t river_index = std::tuple_size<std::tuple<R_Tuple...> >::value - std::tuple_size<std::tuple<L_Tuple...> >::value;
        return std::tuple_cat(std::make_tuple(srook::forward<Args>(args)...), tuple_split_adaptor<river_index>::apply(r));
    }
};

template <>
struct tuple_vector_operation_resulter<false> {
    template <template <class> class Operator, class... L_Tuple, class... R_Tuple, std::size_t index, bool rc, class... Args>
    static SROOK_CONSTEXPR std::tuple<L_Tuple..., R_Tuple...>
    apply(const std::tuple<L_Tuple...>& l, const std::tuple<R_Tuple...>&, std::integral_constant<std::size_t, index>, std::integral_constant<bool, rc>, Args&&... args)
    {
        SROOK_CONSTEXPR std::size_t river_index = std::tuple_size<std::tuple<L_Tuple...> >::value - std::tuple_size<std::tuple<R_Tuple...> >::value;
        return std::tuple_cat(std::make_tuple(srook::forward<Args>(args)...), tuple_split_adaptor<river_index>::apply(l));
    }
};

struct tuple_Vec_impl {
    struct unpacker {
        template <template <class> class Operator, class... L_Tuple, class... R_Tuple, std::size_t index, bool right_is_bigger, class... Args>
        static SROOK_CONSTEXPR std::tuple<L_Tuple..., R_Tuple...>
        apply(const std::tuple<L_Tuple...>& l, const std::tuple<R_Tuple...>& r, std::integral_constant<std::size_t, index>, std::integral_constant<bool, right_is_bigger> rc, Args&&... args)
        {
            return tuple_Vec_impl::apply<Operator>(
                l, r,
                std::integral_constant<std::size_t, index - 1>(),
                srook::move(rc),
                Operator<typename decay<decltype(std::get<index>(l))>::type>()(std::get<index>(l), std::get<index>(r)),
                srook::forward<Args>(args)...);
        }
    };

    template <template <class> class Operator, class... L_Tuple, class... R_Tuple, std::size_t index, bool right_is_bigger, class... Args>
    static SROOK_CONSTEXPR auto
    apply(const std::tuple<L_Tuple...>& l, const std::tuple<R_Tuple...>& r, std::integral_constant<std::size_t, index> ic, std::integral_constant<bool, right_is_bigger> rc, Args&&... args)
        -> decltype(typename conditional<
                    (right_is_bigger ? std::tuple_size<std::tuple<L_Tuple...> >::value : std::tuple_size<std::tuple<R_Tuple...> >::value) == sizeof...(args),
                    detail::tuple_vector_operation_resulter<right_is_bigger>,
                    detail::tuple_Vec_impl::unpacker>::type::template apply<Operator>(l, r, srook::move(ic), srook::move(rc), srook::forward<Args>(args)...))
    {
        return typename conditional<
            (right_is_bigger ? std::tuple_size<std::tuple<L_Tuple...> >::value : std::tuple_size<std::tuple<R_Tuple...> >::value) == sizeof...(args),
            detail::tuple_vector_operation_resulter<right_is_bigger>,
            detail::tuple_Vec_impl::unpacker>::type::template apply<Operator>(l, r, srook::move(ic), srook::move(rc), srook::forward<Args>(args)...);
    }

    template <template <class> class Operator, class... L_Tuple, class... R_Tuple>
    static SROOK_CONSTEXPR auto tuple_Vec(const std::tuple<L_Tuple...>& l, const std::tuple<R_Tuple...>& r)
        -> decltype(apply<Operator>(l, r, std::integral_constant<std::size_t, std::min(std::tuple<std::tuple<L_Tuple...> >::value, std::tuple_size<std::tuple<R_Tuple...> >::value) - 1>(), std::integral_constant < bool, std::tuple_size<std::tuple<L_Tuple...> >::value<std::tuple_size<std::tuple<R_Tuple...> >::value>()))
    {
        return apply<Operator>(
            l, r,
            std::integral_constant<
                std::size_t,
                std::min(std::tuple_size<std::tuple<L_Tuple...> >::value, std::tuple_size<std::tuple<R_Tuple...> >::value) - 1>(),
            std::integral_constant < bool, std::tuple_size<std::tuple<L_Tuple...> >::value<std::tuple_size<std::tuple<R_Tuple...> >::value>());
    }
};

struct TPL_impl {
    template <template <class> class Operator, class Tuple, class Head_tuple, class... Tpl>
    static SROOK_CONSTEXPR std::tuple<Tpl...> tuple_vector_operation_impl(Tuple&& t, Head_tuple&& head, Tpl&&... tpl)
    {
        return tuple_vector_operation_impl<Operator>(tuple_Vec_impl::tuple_Vec<Operator>(srook::forward<Tuple>(t), srook::forward<Head_tuple>(head)), srook::forward<Tpl>(tpl)...);
    }

    template <template <class> class Operator, class Tuple>
    static SROOK_CONSTEXPR Tuple tuple_vector_operation_impl(Tuple&& t)
    {
        return t;
    }
};

} // namespace detail

template <template <class> class Operator, class FirstTpl, class... Tpl, REQUIRES(is_tuple<FirstTpl>::value and conjunction<is_tuple<Tpl>...>::value)>
SROOK_CONSTEXPR auto vector_operation(FirstTpl&& tpl, Tpl&&... tpls)
-> decltype(detail::TPL_impl::template tuple_vector_operation_impl<Operator>(srook::forward<FirstTpl>(tpl), srook::forward<Tpl>(tpls)...))
{
    return detail::TPL_impl::template tuple_vector_operation_impl<Operator>(srook::forward<FirstTpl>(tpl), srook::forward<Tpl>(tpls)...);
}

} // namespace v1
} // namespace numeric

using numeric::vector_operation;

} // namespace tuple
} // namespace srook
#endif
