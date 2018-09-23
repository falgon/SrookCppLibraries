#ifndef INCLUDED_SROOK_MATH_VECTOR_EXPRESSION_HPP
#define INCLUDED_SROOK_MATH_VECTOR_EXPRESSION_HPP

#include <srook/math/vector/impl.h>
#include <srook/tmpl/vt/all.hpp>
#include <srook/tmpl/vt/foldr1.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/zip_with.hpp>
#include <srook/type_traits/detail/has_type_gen.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/is_equality_comparable.hpp>
#include <srook/utility/forward.hpp>

#include <ostream>

SROOK_NESTED_NAMESPACE(srook, math) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

SROOK_TT_DEF_HAS_TYPE_IMPL(exp_tag);
SROOK_TT_DEF_HAS_TYPE(exp_tag);

template <class L, class Operator, class R>
struct Expression {
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

    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR std::size_t size = L::size;
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, SROOK_DEDUCED_TYPENAME L::packed_type, SROOK_DEDUCED_TYPENAME R::packed_type>::type packed_type;

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
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, SROOK_DEDUCED_TYPENAME Exp::packed_type>::type vec_type;
        return dot_product(vec_type(exp));
    }
private:
    const L l_;
    const R r_;
    
    friend std::ostream& operator<<(std::ostream& os, const Expression& exp)
    {
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector_impl, packed_type>::type vec_type;
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
} SROOK_NESTED_NAMESPACE_END(math, srook)
#endif
