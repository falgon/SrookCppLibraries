// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_COMPARE_CATEGORIES_STRONG_ORDERING_HPP
#define INCLUDED_SROOK_COMPARE_CATEGORIES_STRONG_ORDERING_HPP

#include <srook/config.hpp>
#include <srook/utility.hpp>
#include <srook/compare/categories/partial_ordering.hpp>
#include <srook/compare/categories/strong_equality.hpp>
#include <srook/compare/categories/weak_ordering.hpp>

#if defined(SROOK_HAS_STD_COMPARE_HEADER) || SROOK_HAS_INCLUDE(<compare>)
#   include <compare>
#   ifndef SROOK_HAS_STD_COMPARE_HEADER
#       define SROOK_HAS_STD_COMPARE_HEADER 1
#   endif
#endif

namespace srook {
namespace comparison {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_STD_COMPARE_HEADER

class strong_ordering : protected std::strong_ordering {
    typedef std::strong_ordering base_type;
public:
    using base_type::base_type;
    using base_type::less;
    using base_type::equal;
    using base_type::equivalent;
    using base_type::greater;
    using base_type::operator==;
    using base_type::operator!=;
    using base_type::operator<;
    using base_type::operator<=;
    using base_type::operator>;
    using base_type::operator>=;
    using base_type::operator std::weak_equality;
    using base_type::operator std::strong_equality;
    using base_type::operator std::partial_ordering;
    using base_type::operator std::weak_ordering;
    
    SROOK_CONSTEXPR operator weak_equality() const SROOK_NOEXCEPT_TRUE
    {
        return !this->value ? weak_equality::equivalent : weak_equality::nonequivalent;
    }
};

#else

class strong_ordering {
    int value;

    explicit SROOK_CONSTEXPR strong_ordering(eq v) : value(int(v)) {}
    explicit SROOK_CONSTEXPR strong_ordering(ord v) : value(int(v)) {}
public:
    static const strong_ordering less;
    static const strong_ordering equal;
    static const strong_ordering equivalent;
    static const strong_ordering greater;

#define DEF_RELOP(OP)\
    template <class U, SROOK_REQUIRES(type_traits::detail::Lnot<is_same<strong_ordering, SROOK_DEDUCED_TYPENAME decay<U>::type>>::value)>  \
    friend SROOK_CONSTEXPR bool operator OP(strong_ordering v, U&&) SROOK_NOEXCEPT_TRUE                                                    \
    {                                                                                                                                    \
        return v.value OP 0;                                                                                                             \
    }                                                                                                                           
    DEF_RELOP(==)
    DEF_RELOP(!=)
    DEF_RELOP(<)
    DEF_RELOP(<=)
    DEF_RELOP(>)
    DEF_RELOP(>=)
#undef DEF_RELOP
#define DEF_RELOP(OP)\
    template <class U, SROOK_REQUIRES(type_traits::detail::Lnot<is_same<strong_ordering, SROOK_DEDUCED_TYPENAME decay<U>::type>>::value)>  \
    friend SROOK_CONSTEXPR bool operator OP(U&&, strong_ordering v) SROOK_NOEXCEPT_TRUE                                                    \
    {                                                                                                                                    \
        return 0 OP v.value;                                                                                                             \
    }
    DEF_RELOP(==)
    DEF_RELOP(!=)
    DEF_RELOP(<)
    DEF_RELOP(<=)
    DEF_RELOP(>)
    DEF_RELOP(>=)
#undef DEF_RELOP

    SROOK_CONSTEXPR operator weak_equality() const SROOK_NOEXCEPT_TRUE
    {
        return !value ? weak_equality::equivalent : weak_equality::nonequivalent;
    }
    SROOK_CONSTEXPR operator strong_equality() const SROOK_NOEXCEPT_TRUE
    {
        return !value ? strong_equality::equal : strong_equality::nonequal;
    }
    SROOK_CONSTEXPR operator partial_ordering() const SROOK_NOEXCEPT_TRUE
    {
        return !value ? partial_ordering::equivalent : value < 0 ? partial_ordering::less : partial_ordering::greater;
    }
    SROOK_CONSTEXPR operator weak_ordering() const SROOK_NOEXCEPT_TRUE
    {
        return !value ? weak_ordering::equivalent : value < 0 ? weak_ordering::less : weak_ordering::greater;
    }
};

SROOK_INLINE_VARIABLE SROOK_CONSTEXPR strong_ordering strong_ordering::less(ord::less);
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR strong_ordering strong_ordering::equal(eq::equal);
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR strong_ordering strong_ordering::equivalent(eq::equivalent);
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR strong_ordering strong_ordering::greater(ord::greater);

#endif

SROOK_INLINE_NAMESPACE_END
} // namespace comparison
} // namespace srook

#endif
