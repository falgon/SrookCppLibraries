// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_MATRIX_ELEMENTARY_SWAP_HPP
#define INCLUDED_SROOK_MATH_MATRIX_ELEMENTARY_SWAP_HPP
#include <srook/config.hpp>
#include <tuple>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/at.hpp>
#include <srook/tmpl/vt/take.hpp>
#include <srook/tmpl/vt/drop.hpp>
#include <srook/tmpl/vt/size.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/tuple/algorithm/take.hpp>
#include <srook/tuple/algorithm/drop.hpp>


SROOK_NESTED_NAMESPACE(srook, tuple) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t I1, std::size_t I2, class... Ts>
struct swaped_type
    : tmpl::vt::transfer<
        std::tuple,
            SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                SROOK_DEDUCED_TYPENAME tmpl::vt::concat<SROOK_DEDUCED_TYPENAME tmpl::vt::take<I1, Ts...>::type, SROOK_DEDUCED_TYPENAME tmpl::vt::at<I2, Ts...>::type>::type,
                    SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                        SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                            SROOK_DEDUCED_TYPENAME tmpl::vt::drop<I1 + 1, SROOK_DEDUCED_TYPENAME tmpl::vt::take<I2, Ts...>::type>::type,
                            SROOK_DEDUCED_TYPENAME tmpl::vt::at<I1, Ts...>::type
                        >::type,
                        SROOK_DEDUCED_TYPENAME tmpl::vt::drop<I2 + 1, Ts...>::type
                    >::type
            >::type
        > {};

template <std::size_t I, class... Ts>
struct swaped_type<I, I, Ts...>
    : tmpl::vt::transfer<std::tuple, Ts...> {};

template <std::size_t I1, std::size_t I2, class... Ts>
struct swap_impl {
    typedef SROOK_DEDUCED_TYPENAME swaped_type<I1, I2, Ts...>::type result_type;
    
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR result_type
    exec(const std::tuple<Ts...>& ts) SROOK_NOEXCEPT_TRUE
    {
        return
            std::tuple_cat(
                std::tuple_cat(tuple::take<I1>(ts), std::make_tuple(std::get<I2>(ts))), 
                std::tuple_cat(std::tuple_cat(tuple::drop<I1 + 1>(tuple::take<I2>(ts)), std::make_tuple(std::get<I1>(ts))), tuple::drop<I2 + 1>(ts))); 
    }
};

template <std::size_t I, class... Ts>
struct swap_impl<I, I, Ts...> {
    typedef SROOK_DEDUCED_TYPENAME swaped_type<I, I, Ts...>::type result_type;

    SROOK_FORCE_INLINE static SROOK_CONSTEXPR result_type
    exec(const std::tuple<Ts...>& ts) SROOK_NOEXCEPT_TRUE
    {
        return ts;
    }
};

template <std::size_t I1, std::size_t I2, class... Ts>
struct swap_type 
    : conditional<(I1 < I2), swap_impl<I1, I2, Ts...>, swap_impl<I2, I1, Ts...>> {};

template <std::size_t I1, std::size_t I2, class... Ts>
struct swap_result_type 
    : type_constant<SROOK_DEDUCED_TYPENAME swap_type<I1, I2, Ts...>::type::result_type> {};

} // namespace detail

template <std::size_t I1, std::size_t I2, class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
SROOK_DEDUCED_TYPENAME detail::swap_result_type<I1, I2, Ts...>::type
swap(const std::tuple<Ts...>& ts) SROOK_NOEXCEPT_TRUE
{
    return detail::swap_type<I1, I2, Ts...>::type::exec(ts); 
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(tuple, srook)

#endif
