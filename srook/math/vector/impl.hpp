// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_GEOMETORY_FUNDAMENTAL_VECTOR_IMPL_HPP
#define INCLUDED_SROOK_MATH_GEOMETORY_FUNDAMENTAL_VECTOR_IMPL_HPP

#ifndef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/math/vector/impl.h>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/algorithm/for_each.hpp>
#include <srook/config/libraries/optional.hpp>
#include <srook/cstdfloat.hpp>
#include <srook/math/vector/expression.hpp>
#include <srook/math/constants/algorithm/abs.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/utility/index_sequence.hpp>
#include <srook/math/constants/algorithm/sqrt.hpp>
#include <srook/optional.hpp>

#include <srook/tmpl/vt/and.hpp>
#include <srook/tmpl/vt/any.hpp>
#include <srook/tmpl/vt/at.hpp>
#include <srook/tmpl/vt/apply.hpp>
#include <srook/tmpl/vt/compare.hpp>
#include <srook/tmpl/vt/composition.hpp>
#include <srook/tmpl/vt/boolean.hpp>
#include <srook/tmpl/vt/ignore.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/replicate.hpp>
#include <srook/tmpl/vt/foldr1.hpp>
#include <srook/tmpl/vt/zip_with.hpp>

#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/is_nothrow_constructible.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/is_convertible.hpp>
#include <srook/type_traits/detail/has_type_gen.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_equality_comparable.hpp>
#include <srook/type_traits/is_floating_point.hpp>

#include <srook/tuple/algorithm/replicate.hpp>

SROOK_NESTED_NAMESPACE(srook, math) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class... Ts, class L, class Operator, class R, std::size_t s>
SROOK_FORCE_INLINE SROOK_CONSTEXPR vector_impl<Ts...>&
vector_impl_calculate(vector_impl<Ts...>& this_, const Expression<L, Operator, R, s>&, srook::index_sequence<>) SROOK_NOEXCEPT_TRUE 
{
    return this_;
}

template <class... Ts, class L, class Operator, class R, std::size_t s, std::size_t I1, std::size_t... Is>
SROOK_FORCE_INLINE SROOK_CONSTEXPR vector_impl<Ts...>& 
vector_impl_calculate(vector_impl<Ts...>& v, const Expression<L, Operator, R, s>& exp, srook::index_sequence<I1, Is...>)
{
    return v.template get<I1>() = SROOK_DEDUCED_TYPENAME std::tuple_element<I1, vector_impl<Ts...>>::type(exp.template get<I1>()), vector_impl_calculate(v, exp, srook::index_sequence<Is...>{});
}

#if !SROOK_CPP_FOLD_EXPRESSIONS
SROOK_FORCE_INLINE SROOK_CONSTEXPR int accumulate_impl2() SROOK_NOEXCEPT_TRUE
{
    return 0;
}

template <class T, class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<std::common_type, SROOK_DEDUCED_TYPENAME decay<T>::type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>::type
accumulate_impl2(T&& t, Ts&&... ts)
{
    return srook::forward<T>(t) + accumulate_impl2(srook::forward<Ts>(ts)...);
}
#endif

template <class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<std::common_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>::type
accumulate_impl(Ts&&... ts)
{
#if SROOK_CPP_FOLD_EXPRESSIONS
    return (srook::forward<Ts>(ts) + ...);
#else
    return accumulate_impl2(srook::forward<Ts>(ts)...);
#endif
}

template <class... Ts, std::size_t... Is>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<std::common_type, Ts...>::type
accumulate_impl(const vector_impl<Ts...>& v, index_sequence<Is...>)
{
    return accumulate_impl(v.template get<Is>()...);
}

template <class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<std::common_type, Ts...>::type
accumulate(const vector_impl<Ts...>& v)
{
    return accumulate_impl(v, SROOK_DEDUCED_TYPENAME make_index_sequence_type<sizeof...(Ts)>::type());
}

template <class... Ts>
class vector_impl {
public:
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR std::size_t size = sizeof...(Ts);
    typedef SROOK_DEDUCED_TYPENAME conditional<(sizeof...(Ts) > 0), std::tuple<Ts...>, SROOK_NULLOPT_T>::type elems_type;
    typedef SROOK_DEDUCED_TYPENAME conditional<(sizeof...(Ts) > 0), tmpl::vt::packer<Ts...>, tmpl::vt::packer<>>::type packed_type;
protected:
    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector_impl(SROOK_FALSE_TYPE) SROOK_NOEXCEPT_TRUE
        : elems_(SROOK_NULLOPT) {}

    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector_impl(SROOK_TRUE_TYPE) SROOK_NOEXCEPT(is_nothrow_constructible<elems_type&, elems_type>::value)
        : elems_(std::tuple<Ts...>{}) {}
public:
    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector_impl() SROOK_NOEXCEPT(is_nothrow_constructible<elems_type&, elems_type>::value)
        : vector_impl(SROOK_DEDUCED_TYPENAME detail::is_onemore<Ts...>::type()) {}

    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector_impl(const vector_impl&) SROOK_DEFAULT
    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector_impl& operator=(const vector_impl&) SROOK_DEFAULT

    template <class... Us, 
    SROOK_REQUIRES(tmpl::vt::eq<tmpl::vt::packer<SROOK_DEDUCED_TYPENAME decay<Ts>::type...>, tmpl::vt::packer<SROOK_DEDUCED_TYPENAME decay<Us>::type...>>::value)>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector_impl(Us&&... us) SROOK_NOEXCEPT(is_nothrow_constructible<std::tuple<Ts...>, Us&&...>::value)
        : elems_(srook::forward<Us>(us)...) {}

    template <class... Us,
    SROOK_REQUIRES(tmpl::vt::eq<tmpl::vt::packer<SROOK_DEDUCED_TYPENAME decay<Ts>::type...>, tmpl::vt::packer<SROOK_DEDUCED_TYPENAME decay<Us>::type...>>::value)>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector_impl(const std::tuple<Us...>& us) SROOK_NOEXCEPT(is_nothrow_constructible<std::tuple<Ts...>, Us&&...>::value)
        : elems_(us) {}

    template <class L, class Operator, class R, std::size_t s>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector_impl(const srook::math::detail::Expression<L, Operator, R, s>& exp)
    {
        detail::vector_impl_calculate(*this, exp, SROOK_DEDUCED_TYPENAME srook::make_index_sequence_type<sizeof...(Ts)>::type());
    }

    template <class L, class Operator, class R, std::size_t s>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector_impl& operator=(const srook::math::detail::Expression<L, Operator, R, s>& exp)
    {
        return detail::vector_impl_calculate(*this, exp, SROOK_DEDUCED_TYPENAME srook::make_index_sequence_type<size>::type());
    }

    template <std::size_t I>
    SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
    tmpl::vt::boolean<tmpl::vt::ignore<SROOK_NULLOPT_T>::template generate, detail::index_bind<I>::template generate, detail::is_onemore, Ts...>::type&
    get() SROOK_NOEXCEPT_TRUE 
    {
        return std::get<I>(elems_); 
    }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    template <std::size_t I>
    SROOK_CONSTEXPR const SROOK_DEDUCED_TYPENAME
    tmpl::vt::boolean<tmpl::vt::ignore<SROOK_NULLOPT_T>::template generate, detail::index_bind<I>::template generate, detail::is_onemore, Ts...>::type&
    get() const SROOK_NOEXCEPT_TRUE
    {
        return std::get<I>(elems_);
    }
#endif

    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool is_unit() const SROOK_NOEXCEPT_TRUE
    {
        return srook::math::abs(length() - 1) < numeric_limits<SROOK_DECLTYPE(length())>::epsilon();
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::floatmax_t length() const SROOK_NOEXCEPT_TRUE
    {
        return length_impl(SROOK_DEDUCED_TYPENAME make_index_sequence_type<size>::type());
    }

    SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR bool normalize() SROOK_NOEXCEPT_TRUE
    {
        const srook::floatmax_t len = length();
        return len ? *this /= len, true : false;
    }

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    template <class RoundType = srook::floatmax_t>
#else
    template <class RoundType>
#endif
    SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR SROOK_DEDUCED_TYPENAME 
    enable_if<
        is_arithmetic<RoundType>::value,
        srook::optional<
            SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
                vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, packed_type, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<size, RoundType>::type>::type
            >::type
        >
    >::type
    get_normalized() const SROOK_NOEXCEPT_TRUE
    {
        typedef 
            SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
                vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, packed_type, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<size, RoundType>::type>::type
            >::type result_type;
        const RoundType len = RoundType(length());
        return len ? srook::make_optional(result_type(*this / length())) : srook::nullopt;
    }

    template <class... Us>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            bool_constant<size == sizeof...(Us)>,
            tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, packed_type, tmpl::vt::packer<Us...>>::type>
        >::value,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, packed_type, tmpl::vt::packer<Us...>>::type>::type
    >::type
    projection(const vector_impl<Us...>& other) const SROOK_NOEXCEPT_TRUE
    {
        return other * dot_product(other) / (other.length() * other.length());
    }

    template <class... Us,
    SROOK_REQUIRES(
        type_traits::detail::Land<
            type_traits::detail::Lnot<is_same<vector_impl, SROOK_DEDUCED_TYPENAME decay<Us>::type>>...,
            bool_constant<size == sizeof...(Us)>,
            tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, packed_type, tmpl::vt::packer<SROOK_DEDUCED_TYPENAME decay<Us>::type...>>::type>
        >::value
    )>
    SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
    tmpl::vt::transfer<
        vector_impl, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, packed_type, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, Us...>::type>::type 
    >::type
    projection(Us&&... us) const SROOK_NOEXCEPT_TRUE
    {
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, Us...>::type>::type vec_type;
        return projection(vec_type(srook::forward<Us>(us)...));
    }

    template <class... Us>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            bool_constant<size == sizeof...(Us)>,
            tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, packed_type, tmpl::vt::packer<Us...>>::type>
        >::value,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, packed_type, tmpl::vt::packer<Us...>>::type>::type
    >::type
    perpendicular(const vector_impl<Us...>& other) const SROOK_NOEXCEPT_TRUE
    {
        return *this - projection(other);
    }
    
    template <class... Us,
    SROOK_REQUIRES(
        type_traits::detail::Land<
            type_traits::detail::Lnot<is_same<vector_impl, SROOK_DEDUCED_TYPENAME decay<Us>::type>>...,
            bool_constant<size == sizeof...(Us)>,
            tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, packed_type, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, Us...>::type>::type>
        >::value
    )>
    SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        vector_impl, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, packed_type, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, Us...>::type>::type
    >::type
    perpendicular(Us&&... us) const SROOK_NOEXCEPT_TRUE
    {
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, Us...>::type>::type vec_type;
        return perpendicular(vec_type(srook::forward<Us>(us)...));
    }

    template <class... Us>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            bool_constant<sizeof...(Ts) == sizeof...(Us)>,
            tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, tmpl::vt::packer<Ts...>, tmpl::vt::packer<Us...>>::type>
        >::value,
        SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<std::common_type, SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, tmpl::vt::packer<Ts...>, tmpl::vt::packer<Us...>>::type>::type
    >::type
    dot_product(const vector_impl<Us...>& rhs) const
    {
        typedef srook::math::detail::Expression<vector_impl<Ts...>, std::multiplies<>, vector_impl<Us...>> expression_type;
        typedef 
            SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, tmpl::vt::packer<Ts...>, tmpl::vt::packer<Us...>>::type>::type 
        vec_type;
        
        return detail::accumulate(vec_type(expression_type(*this, rhs)));
    }

    template <class Exp>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            detail::has_exp_tag<Exp>,
            bool_constant<Exp::size == sizeof...(Ts)>
        >::value, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<
            std::common_type, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, tmpl::vt::packer<Ts...>, SROOK_DEDUCED_TYPENAME Exp::packed_type>::type
        >::type
    >::type
    dot_product(const Exp& exp) const SROOK_NOEXCEPT_TRUE
    {
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME Exp::packed_type>::type vec_type;
        return dot_product(vec_type(exp));
    }

    template <class... Us,
    SROOK_REQUIRES(
        type_traits::detail::Land<
            type_traits::detail::Lnot<is_same<vector_impl, SROOK_DEDUCED_TYPENAME decay<Us>::type>>...,
            bool_constant<sizeof...(Ts) == sizeof...(Us)>,
            tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, packed_type, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, Us...>::type>::type>
        >::value
    )>
    SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
    tmpl::vt::foldr1<std::common_type, SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, packed_type, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, Us...>::type>::type>::type
    dot_product(Us&&... us) const
    {
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, Us...>::type>::type vec_type;
        return dot_product(vec_type(srook::forward<Us>(us)...));
    }

    template <class... Us>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR 
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            bool_constant<size == sizeof...(Us)>, 
            tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, packed_type, tmpl::vt::packer<Us...>>::type>
        >::value, 
        vector_impl&
    >::type operator+=(const vector_impl<Us...>& other)
    {
        return *this = *this + other;
    }
    
    template <class Exp>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            detail::has_exp_tag<Exp>,
            bool_constant<Exp::size == sizeof...(Ts)>
        >::value, 
        srook::math::detail::Expression<packed_type, std::plus<>, Exp>
    >::type
    operator+=(const Exp& exp) SROOK_NOEXCEPT_TRUE
    {
        return *this = *this + exp;
    }
    
    template <class... Us>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR 
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            bool_constant<size == sizeof...(Us)>, 
            tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, packed_type, tmpl::vt::packer<Us...>>::type>
        >::value, 
        vector_impl&
    >::type operator-=(const vector_impl<Us...>& other)
    {
        return *this = *this - other;
    }
    
    template <class Exp>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            detail::has_exp_tag<Exp>,
            bool_constant<Exp::size == sizeof...(Ts)>
        >::value,
        vector_impl&
    >::type
    operator-=(const Exp& exp) SROOK_NOEXCEPT_TRUE
    {
        return *this = *this - exp;
    }

    template <class T>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<is_convertible<SROOK_DEDUCED_TYPENAME decay<T>::type, Ts>...>::value,
        vector_impl&
    >::type
    operator*=(T&& val)
    {
        return *this = *this * srook::forward<T>(val);
    }

    template <class T>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<is_convertible<SROOK_DEDUCED_TYPENAME decay<T>::type, Ts>...>::value,
        vector_impl&
    >::type
    operator/=(T&& val)
    {
        return *this = *this / srook::forward<T>(val);
    }
protected:
    elems_type elems_;

    template <std::size_t... Is>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::floatmax_t 
    length_impl(index_sequence<Is...>) const SROOK_NOEXCEPT_TRUE
    {
        return srook::math::sqrt(detail::accumulate(vector_impl(get<Is>() * get<Is>()...)));
    }

    SROOK_FORCE_INLINE std::ostream& 
    output_stream(SROOK_TRUE_TYPE, std::ostream& os) const
    {
        srook::for_each(elems_, [&os](const auto& val) { os << val << " "; });
        return os;
    }

    SROOK_FORCE_INLINE std::ostream& 
    output_stream(SROOK_FALSE_TYPE, std::ostream& os) const
    {
        return os << "Empty";
    }

    friend SROOK_FORCE_INLINE std::ostream&
    operator<<(std::ostream& os, const vector_impl& this_)
    {
        return this_.output_stream(SROOK_DEDUCED_TYPENAME detail::is_onemore<Ts...>::type(), os);
    }
};

// Equality
template <bool>
struct round_err_equal {
    template <class L, class R>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR bool eq(L&& l, R&& r)
    SROOK_NOEXCEPT(tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::map<tmpl::vt::composition<is_nothrow_equality_comparable, decay>::template generate, L, R>::type>::value) 
    {
        return srook::forward<L>(l) == srook::forward<R>(r);
    }
};

template <>
struct round_err_equal<true> {
    template <class L, class R>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR bool eq(L&& l, R&& r)
    {
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::apply<std::common_type, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, L, R>::type>::type cm_type;
        return srook::math::abs(srook::forward<L>(l) - srook::forward<R>(r)) < numeric_limits<cm_type>::epsilon();
    }
};

#if !SROOK_CPP_FOLD_EXPRESSIONS
SROOK_CONSTEXPR bool equality_no_fold() SROOK_NOEXCEPT_TRUE
{
    return true;
}
template <class B, class... Bs>
SROOK_CONSTEXPR bool equality_no_fold(B&& b, Bs&&... bs) SROOK_NOEXCEPT_TRUE
{
    return b && equality_no_fold(srook::forward<Bs>(bs)...);
}
#endif
template <class... Ts, class... Us, std::size_t... Is>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        bool_constant<sizeof...(Ts) == sizeof...(Us)>,
        tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, tmpl::vt::packer<Ts...>, tmpl::vt::packer<Us...>>::type>
    >::value,
    bool
>::type
equality(const vector_impl<Ts...>& lhs, const vector_impl<Us...>& rhs, index_sequence<Is...>)
SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_equality_comparable<Ts>..., is_nothrow_equality_comparable<Us>...>::value)
{
    return [](auto&&... bs){ 
#if SROOK_CPP_FOLD_EXPRESSIONS
        return  (srook::forward<SROOK_DECLTYPE(bs)>(bs) && ...);
#else
        return equality_no_fold(srook::forward<SROOK_DECLTYPE(bs)>(bs)...);
#endif
    }(round_err_equal<
        tmpl::vt::any<
            is_floating_point, 
            SROOK_DEDUCED_TYPENAME decay<SROOK_DECLTYPE(lhs.template get<Is>())>::type, 
            SROOK_DEDUCED_TYPENAME decay<SROOK_DECLTYPE(rhs.template get<Is>())>::type
        >::type::value
    >::eq(lhs.template get<Is>(), rhs.template get<Is>())...);
}

template <class... Ts, class... Us>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        bool_constant<sizeof...(Ts) != sizeof...(Us)>,
        tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, tmpl::vt::packer<Ts...>, tmpl::vt::packer<Us...>>::type>
    >::value,
    bool
>::type
operator==(const vector_impl<Ts...>&, const vector_impl<Us...>&) SROOK_NOEXCEPT_TRUE
{
    return false;
}

template <class... Ts, class... Us>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        bool_constant<sizeof...(Ts) == sizeof...(Us)>,
        tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, tmpl::vt::packer<Ts...>, tmpl::vt::packer<Us...>>::type>
    >::value,
    bool
>::type
operator==(const vector_impl<Ts...>& lhs, const vector_impl<Us...>& rhs) 
SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_equality_comparable<Ts>..., is_nothrow_equality_comparable<Us>...>::value)
{
    return equality(lhs, rhs, SROOK_DEDUCED_TYPENAME make_index_sequence_type<sizeof...(Ts)>::type());
}

template <class... Ts, class... Us>
SROOK_FORCE_INLINE SROOK_CONSTEXPR bool
operator!=(const vector_impl<Ts...>& lhs, const vector_impl<Us...>& rhs) 
SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_equality_comparable<Ts>..., is_nothrow_equality_comparable<Us>...>::value)
{
    return !(lhs == rhs);
}

// Vector sum
template <class... Ts, class... Us>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        bool_constant<(sizeof...(Ts) == sizeof...(Us))>, 
        tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, tmpl::vt::packer<Ts...>, tmpl::vt::packer<Us...>>::type>
    >::value,
    srook::math::detail::Expression<vector_impl<Ts...>, std::plus<>, vector_impl<Us...>>
>::type
operator+(const vector_impl<Ts...>& l, const vector_impl<Us...>& r) SROOK_NOEXCEPT_TRUE
{
    return srook::math::detail::Expression<vector_impl<Ts...>, std::plus<>, vector_impl<Us...>>(l, r);
}

template <class... Ts, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        detail::has_exp_tag<Exp>,
        bool_constant<Exp::size == sizeof...(Ts)>
    >::value, 
    srook::math::detail::Expression<vector_impl<Ts...>, std::plus<>, Exp>
>::type
operator+(const vector_impl<Ts...>& l, const Exp& exp) SROOK_NOEXCEPT_TRUE
{
    return srook::math::detail::Expression<vector_impl<Ts...>, std::plus<>, Exp>(l, exp);
}

template <class... Ts, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        detail::has_exp_tag<Exp>,
        bool_constant<Exp::size == sizeof...(Ts)>
    >::value, 
    srook::math::detail::Expression<Exp, std::plus<>, vector_impl<Ts...>>
>::type
operator+(const Exp& exp, const vector_impl<Ts...>& r) SROOK_NOEXCEPT_TRUE
{
    return srook::math::detail::Expression<Exp, std::plus<>, vector_impl<Ts...>>(exp, r);
}

template <class Exp1, class Exp2>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        detail::has_exp_tag<Exp1>, 
        detail::has_exp_tag<Exp2>,
        bool_constant<Exp1::size == Exp2::size>
    >::value, 
    srook::math::detail::Expression<Exp1, std::plus<>, Exp2>
>::type
operator+(const Exp1& exp1, const Exp2& exp2) SROOK_NOEXCEPT_TRUE
{
    return srook::math::detail::Expression<Exp1, std::plus<>, Exp2>(exp1, exp2);
}

// Vector sub
template <class... Ts, class... Us>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        bool_constant<(sizeof...(Ts) == sizeof...(Us))>, 
        tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, tmpl::vt::packer<Ts...>, tmpl::vt::packer<Us...>>::type>
    >::value,
    srook::math::detail::Expression<vector_impl<Ts...>, std::minus<>, vector_impl<Us...>>
>::type
operator-(const vector_impl<Ts...>& l, const vector_impl<Us...>& r) SROOK_NOEXCEPT_TRUE
{
    return srook::math::detail::Expression<vector_impl<Ts...>, std::minus<>, vector_impl<Us...>>(l, r);
}

template <class... Ts, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        detail::has_exp_tag<Exp>,
        bool_constant<Exp::size == sizeof...(Ts)>
    >::value, 
    srook::math::detail::Expression<vector_impl<Ts...>, std::minus<>, Exp>
>::type
operator-(const vector_impl<Ts...>& l, const Exp& exp) SROOK_NOEXCEPT_TRUE
{
    return srook::math::detail::Expression<vector_impl<Ts...>, std::minus<>, Exp>(l, exp);
}

template <class... Ts, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        detail::has_exp_tag<Exp>,
        bool_constant<Exp::size == sizeof...(Ts)>
    >::value, 
    srook::math::detail::Expression<Exp, std::minus<>, vector_impl<Ts...>>
>::type
operator-(const Exp& exp, const vector_impl<Ts...>& r) SROOK_NOEXCEPT_TRUE
{
    return srook::math::detail::Expression<Exp, std::minus<>, vector_impl<Ts...>>(exp, r);
}

template <class Exp1, class Exp2>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        detail::has_exp_tag<Exp1>, 
        detail::has_exp_tag<Exp2>,
        bool_constant<Exp1::size == Exp2::size>
    >::value, 
    srook::math::detail::Expression<Exp1, std::minus<>, Exp2>
>::type
operator-(const Exp1& exp1, const Exp2& exp2) SROOK_NOEXCEPT_TRUE
{
    return srook::math::detail::Expression<Exp1, std::minus<>, Exp2>(exp1, exp2);
}

// Scalar multiplication
template <class... Ts, class T>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<is_convertible<SROOK_DEDUCED_TYPENAME decay<T>::type, Ts>...>::value,
    srook::math::detail::Expression<
        vector_impl<Ts...>, std::multiplies<>, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<sizeof...(Ts), SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type
    >
>::type
operator*(const vector_impl<Ts...>& v, T&& val)
{
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<sizeof...(Ts), SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type scalar;
    return srook::math::detail::Expression<vector_impl<Ts...>, std::multiplies<>, scalar>(v, tuple::replicate<sizeof...(Ts)>(srook::forward<T>(val)));
}

template <class... Ts, class T>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<is_convertible<SROOK_DEDUCED_TYPENAME decay<T>::type, Ts>...>::value,
    srook::math::detail::Expression<
        vector_impl<Ts...>, std::multiplies<>, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<sizeof...(Ts), SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type
    >
>::type
operator*(T&& val, const vector_impl<Ts...>& v)
{
    return v * srook::forward<T>(val);
}

template <class T, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    detail::has_exp_tag<Exp>::value, 
    srook::math::detail::Expression<
        Exp, std::multiplies<>,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<Exp::size, SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type
    >
>::type
operator*(const Exp& exp, T&& val) SROOK_NOEXCEPT_TRUE
{
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<Exp::size, SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type scalar;
    return srook::math::detail::Expression<Exp, std::multiplies<>, scalar>(exp, tuple::replicate<Exp::size>(srook::forward<T>(val)));
}

template <class T, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    detail::has_exp_tag<Exp>::value, 
    srook::math::detail::Expression<
        Exp, std::multiplies<>,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<Exp::size, SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type
    >
>::type
operator*(T&& val, const Exp& exp) SROOK_NOEXCEPT_TRUE
{
    return exp * srook::forward<T>(val);
}

// Scalar division
template <class... Ts, class T>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<is_convertible<SROOK_DEDUCED_TYPENAME decay<T>::type, Ts>...>::value,
    srook::math::detail::Expression<
        vector_impl<Ts...>, std::divides<>, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<sizeof...(Ts), SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type
    >
>::type
operator/(const vector_impl<Ts...>& v, T&& val)
{
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<sizeof...(Ts), SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type scalar;
    return srook::math::detail::Expression<vector_impl<Ts...>, std::divides<>, scalar>(v, tuple::replicate<sizeof...(Ts)>(srook::forward<T>(val)));
}

template <class T, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    detail::has_exp_tag<Exp>::value, 
    srook::math::detail::Expression<
        Exp, std::divides<>,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<Exp::size, SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type
    >
>::type
operator/(const Exp& exp, T&& val) SROOK_NOEXCEPT_TRUE
{
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<Exp::size, SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type scalar;
    return srook::math::detail::Expression<Exp, std::divides<>, scalar>(exp, tuple::replicate<Exp::size>(srook::forward<T>(val)));
}

} // namespace detail

// inner product
template <class... Ts, class... Us>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        bool_constant<sizeof...(Ts) == sizeof...(Us)>,
        tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, tmpl::vt::packer<Ts...>, tmpl::vt::packer<Us...>>::type>
    >::value,
    SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<std::common_type, SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, tmpl::vt::packer<Ts...>, tmpl::vt::packer<Us...>>::type>::type
>::type
inner_product(const detail::vector_impl<Ts...>& lhs, const detail::vector_impl<Us...>& rhs)
{
    return lhs.dot_product(rhs);
}

template <class... Ts, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        detail::has_exp_tag<Exp>,
        bool_constant<Exp::size == sizeof...(Ts)>
    >::value, 
    SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<
        std::common_type, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, tmpl::vt::packer<Ts...>, SROOK_DEDUCED_TYPENAME Exp::packed_type>::type
    >::type
>::type
inner_product(const detail::vector_impl<Ts...>& lhs, const Exp& exp) SROOK_NOEXCEPT_TRUE
{
    return lhs.dot_product(exp);
}

template <class... Ts, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        detail::has_exp_tag<Exp>,
        bool_constant<Exp::size == sizeof...(Ts)>
    >::value, 
    SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<
        std::common_type, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, tmpl::vt::packer<Ts...>, SROOK_DEDUCED_TYPENAME Exp::packed_type>::type
    >::type
>::type
inner_product(const Exp& exp, const detail::vector_impl<Ts...>& rhs) SROOK_NOEXCEPT_TRUE
{
    return exp.dot_product(rhs);
}

template <class Exp1, class Exp2>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        detail::has_exp_tag<Exp1>, 
        detail::has_exp_tag<Exp2>,
        bool_constant<Exp1::size == Exp2::size>
    >::value, 
    SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<
        std::common_type,
        SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, SROOK_DEDUCED_TYPENAME Exp1::packed_type, SROOK_DEDUCED_TYPENAME Exp2::packed_type>::type
    >::type
>::type
inner_product(const Exp1& exp1, const Exp2& exp2) SROOK_NOEXCEPT_TRUE
{
    return exp1.dot_product(exp2);
}


SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(math, srook)

namespace std {

template <class... Ts>
struct tuple_size<srook::math::detail::vector_impl<Ts...>> : integral_constant<std::size_t, sizeof...(Ts)> {};

template <std::size_t I, class... Ts>
struct tuple_element<I, srook::math::detail::vector_impl<Ts...>> 
    : srook::tmpl::vt::boolean<
        srook::tmpl::vt::ignore<SROOK_NULLOPT_T>::template generate,
        srook::math::detail::index_bind<I>::template generate,
        srook::math::detail::is_onemore,
        Ts...
    > {};

} // namespace std

#endif
#endif
