// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_VECTOR_LINEAR_ALGEBRA_EXPRESSION_HPP
#define INCLUDED_SROOK_MATH_VECTOR_LIBEAR_ALGEBRA_EXPRESSION_HPP

#include <srook/math/linear_algebra/vector/impl.h>
#include <srook/cstdfloat.hpp>
#include <srook/tmpl/vt/all.hpp>
#include <srook/tmpl/vt/boolean.hpp>
#include <srook/tmpl/vt/foldr1.hpp>
#include <srook/tmpl/vt/ignore.hpp>
#include <srook/tmpl/vt/replicate.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/zip_with.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/type_traits/is_arithmetic.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/is_equality_comparable.hpp>
#include <srook/optional.hpp>
#include <srook/utility/forward.hpp>
#include <ostream>

SROOK_NESTED_NAMESPACE(srook, math, linear_algebra) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class L, class Operator, class R, std::size_t = L::size>
struct Expression {
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR std::size_t size = L::size;
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, SROOK_DEDUCED_TYPENAME L::packed_type, SROOK_DEDUCED_TYPENAME R::packed_type>::type packed_type;
private:
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, packed_type>::type vec_type;
public:
    struct exp_tag;

    SROOK_FORCE_INLINE SROOK_CONSTEXPR Expression(const L& l, const R& r) SROOK_NOEXCEPT_TRUE
        : l_(l), r_(r) {}

    template <std::size_t I>
    SROOK_CONSTEXPR auto get() const SROOK_NOEXCEPT(Operator()(declval<L&>().template get<I>(), declval<R&>().template get<I>()))
    -> SROOK_DECLTYPE(Operator()(declval<L&>().template get<I>(), declval<R&>().template get<I>())) 
    {
        typedef SROOK_DECLTYPE(l_.template get<I>()) left_type;
        typedef SROOK_DECLTYPE(r_.template get<I>()) right_type;
        typedef SROOK_DEDUCED_TYPENAME std::common_type<left_type, right_type>::type cm_type;
        return Operator()(cm_type(l_.template get<I>()), cm_type(r_.template get<I>())); 
    }

    template <class... Ts>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<bool_constant<size == sizeof...(Ts)>>::value, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<
            std::common_type, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, tmpl::vt::packer<Ts...>, packed_type>::type
        >::type
    >::type
    dot_product(const vector_impl<Ts...>& r) const SROOK_NOEXCEPT_TRUE
    {
        return r.dot_product(*this);
    }

    template <class Exp>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<detail::has_exp_tag<Exp>, bool_constant<size == Exp::size>>::value, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<
            std::common_type,
            SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, packed_type, SROOK_DEDUCED_TYPENAME Exp::packed_type>::type
        >::type
    >::type
    dot_product(const Exp& exp) const SROOK_NOEXCEPT_TRUE
    {
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME Exp::packed_type>::type other_vec_type;
        return dot_product(other_vec_type(exp));
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::floatmax_t length() const SROOK_NOEXCEPT_TRUE
    {
        return vec_type(*this).length();
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool is_unit() const SROOK_NOEXCEPT_TRUE
    {
        return vec_type(*this).is_unit();
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
        return vec_type(*this).get_normalized();
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
        return vec_type(*this).projection(other);
    }
    
    template <class Exp>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<detail::has_exp_tag<Exp>, bool_constant<size == Exp::size>>::value, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<
            std::common_type,
            SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, packed_type, SROOK_DEDUCED_TYPENAME Exp::packed_type>::type
        >::type
    >::type
    projection(const Exp& exp) const SROOK_NOEXCEPT_TRUE
    {
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME Exp::packed_type>::type other_vec_type;
        return projection(other_vec_type(exp));
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
        return vec_type(*this).perpendicular(other);
    }
    
    template <class Exp>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<detail::has_exp_tag<Exp>, bool_constant<size == Exp::size>>::value, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<
            std::common_type,
            SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, packed_type, SROOK_DEDUCED_TYPENAME Exp::packed_type>::type
        >::type
    >::type
    perpendicular(const Exp& exp) const SROOK_NOEXCEPT_TRUE
    {
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME Exp::packed_type>::type other_vec_type;
        return perpendicular(other_vec_type(exp));
    }
private:
    const L l_;
    const R r_;
    
    friend std::ostream& operator<<(std::ostream& os, const Expression& exp)
    {
        return os << vec_type(exp);
    }
};

template <class L, class Operator, class R, class... Ts>
SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<
        tmpl::vt::all<is_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L, Operator, R>::packed_type>,
        is_equality_comparable<Ts>...
    >::value,
    bool
>::type
operator==(const Expression<L, Operator, R>& lhs, const vector_impl<Ts...>& rhs)
SROOK_NOEXCEPT(type_traits::detail::Land<tmpl::vt::all<is_nothrow_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L, Operator, R>::packed_type>, is_nothrow_equality_comparable<Ts>...>::value)
{
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME Expression<L, Operator, R>::packed_type>::type vec_type;
    return vec_type(lhs) == rhs;
}

template <class L, class Operator, class R, class... Ts>
SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<
        tmpl::vt::all<is_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L, Operator, R>::packed_type>,
        is_equality_comparable<Ts>...
    >::value,
    bool
>::type
operator==(const vector_impl<Ts...>& lhs, const Expression<L, Operator, R>& rhs)
SROOK_NOEXCEPT(type_traits::detail::Land<tmpl::vt::all<is_nothrow_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L, Operator, R>::packed_type>, is_nothrow_equality_comparable<Ts>...>::value)
{
    return rhs == lhs;
}

template <class L1, class L2, class Operator1, class Operator2, class R1, class R2>
SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<
        tmpl::vt::all<is_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L1, Operator1, R1>::packed_type>,
        tmpl::vt::all<is_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L2, Operator2, R2>::packed_type>
    >::value,
    bool
>::type
operator==(const Expression<L1, Operator1, R1>& lhs, const Expression<L2, Operator2, R2>& rhs)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        tmpl::vt::all<is_nothrow_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L1, Operator1, R1>::packed_type>, 
        tmpl::vt::all<is_nothrow_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L2, Operator2, R2>::packed_type>
    >::value
)
{
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME Expression<L1, Operator1, R1>::packed_type>::type vec_type;
    return vec_type(lhs) == rhs;
}

template <class L, class Operator, class R, class... Ts>
SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<
        tmpl::vt::all<is_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L, Operator, R>::packed_type>,
        is_equality_comparable<Ts>...
    >::value,
    bool
>::type
operator!=(const Expression<L, Operator, R>& lhs, const vector_impl<Ts...>& rhs)
SROOK_NOEXCEPT(type_traits::detail::Land<tmpl::vt::all<is_nothrow_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L, Operator, R>::packed_type>, is_nothrow_equality_comparable<Ts>...>::value)
{
    return !(lhs == rhs);
}

template <class L, class Operator, class R, class... Ts>
SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<
        tmpl::vt::all<is_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L, Operator, R>::packed_type>,
        is_equality_comparable<Ts>...
    >::value,
    bool
>::type
operator!=(const vector_impl<Ts...>& lhs, const Expression<L, Operator, R>& rhs)
SROOK_NOEXCEPT(type_traits::detail::Land<tmpl::vt::all<is_nothrow_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L, Operator, R>::packed_type>, is_nothrow_equality_comparable<Ts>...>::value)
{
    return !(lhs == rhs);
}

template <class L1, class L2, class Operator1, class Operator2, class R1, class R2>
SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<
        tmpl::vt::all<is_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L1, Operator1, R1>::packed_type>,
        tmpl::vt::all<is_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L2, Operator2, R2>::packed_type>
    >::value,
    bool
>::type
operator!=(const Expression<L1, Operator1, R1>& lhs, const Expression<L2, Operator2, R2>& rhs)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        tmpl::vt::all<is_nothrow_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L1, Operator1, R1>::packed_type>, 
        tmpl::vt::all<is_nothrow_equality_comparable, SROOK_DEDUCED_TYPENAME Expression<L2, Operator2, R2>::packed_type>
    >::value
)
{
    return !(lhs == rhs);
}

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linear_algebra, math, srook)
#endif
