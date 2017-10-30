// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TUPLE_ROTATE_HPP
#define INCLUDED_SROOK_TUPLE_ROTATE_HPP
#include <srook/mpl/variadic_player.hpp>
#include <srook/type_traits/conditional.hpp>
#include <tuple>

namespace srook {
namespace tuple{
inline namespace v1{
namespace detail {

struct Applyer_Rotate {

    struct invoker {
	template <class... Ts, std::size_t v, bool b, class... Args>
	static constexpr Transfer_t<std::tuple, Concat_t<Last_t<Ts...>, PopBack_t<Ts...>>>
	apply(const std::tuple<Ts...> &, std::integral_constant<std::size_t, v>, std::integral_constant<bool, b>, Args &&... args)
	{
	    return std::make_tuple(std::forward<Args>(args)...);
	}
    };

    struct unpacker {
	struct first {
	    template <class... Ts, std::size_t v, bool b, class... Args>
	    static constexpr Transfer_t<std::tuple, Concat_t<Last_t<Ts...>, PopBack_t<Ts...>>>
	    apply(const std::tuple<Ts...> &t, std::integral_constant<std::size_t, v> inc, std::integral_constant<bool, b>, Args &&... args)
	    {
		return Applyer_Rotate::apply(t, std::move(inc), std::integral_constant<bool, false>(), std::get<std::tuple_size<std::tuple<Ts...>>::value - 1>(t), std::forward<Args>(args)...);
	    }
	};
	struct not_first {
	    template <class... Ts, std::size_t v, bool b, class... Args>
	    static constexpr Transfer_t<std::tuple, Concat_t<Last_t<Ts...>, PopBack_t<Ts...>>>
	    apply(const std::tuple<Ts...> &t, std::integral_constant<std::size_t, v>, std::integral_constant<bool, b> ib, Args &&... args)
	    {
		return Applyer_Rotate::apply(t, std::integral_constant<std::size_t, v + 1>(), std::move(ib), std::forward<Args>(args)..., std::get<v>(t));
	    }
	};

	template <class... Ts, std::size_t v, bool b, class... Args>
	static constexpr Transfer_t<std::tuple, Concat_t<Last_t<Ts...>, PopBack_t<Ts...>>>
	apply(const std::tuple<Ts...> &t, std::integral_constant<std::size_t, v> ic, std::integral_constant<bool, b> ib, Args &&... args)
	{
	    return typename conditional<b, first, not_first>::type::apply(t, std::move(ic), std::move(ib), std::forward<Args>(args)...);
	}
    };

    template <class... Ts, std::size_t v, bool b, class... Args>
    static constexpr Transfer_t<std::tuple, Concat_t<Last_t<Ts...>, PopBack_t<Ts...>>>
    apply(const std::tuple<Ts...> &t, std::integral_constant<std::size_t, v> ic, std::integral_constant<bool, b> ib, Args &&... args)
    {
	return typename conditional<sizeof...(args) == std::tuple_size<std::tuple<Ts...>>::value, invoker, unpacker>::type::apply(t, std::move(ic), std::move(ib), std::forward<Args>(args)...);
    }
};

} // namespace detail

template <class... Ts>
constexpr Transfer_t<std::tuple, Concat_t<Last_t<Ts...>, PopBack_t<Ts...>>> rotate(const std::tuple<Ts...> &t)
{
    return detail::Applyer_Rotate::apply(t, std::integral_constant<std::size_t, 0>(), std::integral_constant<bool, true>());
}

} // inline namespace v1
} // namespace tuple
} // namespace srook

#endif
