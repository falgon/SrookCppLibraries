// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_COMPARE_CATEGORIES_PARTIAL_ORDERING_HPP
#define INCLUDED_SROOK_COMPARE_CATEGORIES_PARTIAL_ORDERING_HPP

#include <srook/config.hpp>
#include <srook/utility.hpp>
#include <srook/compare/categories/weak_equality.hpp>

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

class partial_ordering : protected std::partial_ordering {
    typedef std::partial_ordering base_type;
public:
    using base_type::base_type;
    using base_type::less;
    using base_type::equivalent;
    using base_type::greater;
    using base_type::unordered;
    using base_type::operator==;
    using base_type::operator!=;
    using base_type::operator<;
    using base_type::operator<=;
    using base_type::operator>;
    using base_type::operator>=;
    using base_type::operator std::weak_equality;
    
    SROOK_CONSTEXPR operator weak_equality() const SROOK_NOEXCEPT_TRUE
    {
        return !this->value ? weak_equality::equivalent : weak_equality::nonequivalent;
    }
};

#else

class partial_ordering {
    int value;
    bool is_ordered;

    explicit SROOK_CONSTEXPR partial_ordering(eq v) : value(int(v)), is_ordered(true) {}
    explicit SROOK_CONSTEXPR partial_ordering(ord v) : value(int(v)), is_ordered(true) {}
    explicit SROOK_CONSTEXPR partial_ordering(ncmp v) : value(int(v)), is_ordered(false) {}
public:
    static const partial_ordering less;
    static const partial_ordering equivalent;
    static const partial_ordering greater;
    static const partial_ordering unordered;

#define DEF_RELOP(OP)\
    template <class U, SROOK_REQUIRES(type_traits::detail::Lnot<is_same<partial_ordering, SROOK_DEDUCED_TYPENAME decay<U>::type>>::value)>  \
    friend SROOK_CONSTEXPR bool operator OP(partial_ordering v, U&&) SROOK_NOEXCEPT_TRUE                                                    \
    {                                                                                                                                       \
        return v.is_ordered && v.value OP 0;                                                                                                \
    }                                                                                                                           
    DEF_RELOP(==)
    DEF_RELOP(<)
    DEF_RELOP(<=)
    DEF_RELOP(>)
    DEF_RELOP(>=)
#undef DEF_RELOP
#define DEF_RELOP(OP)\
    template <class U, SROOK_REQUIRES(type_traits::detail::Lnot<is_same<partial_ordering, SROOK_DEDUCED_TYPENAME decay<U>::type>>::value)>  \
    friend SROOK_CONSTEXPR bool operator OP(U&&, partial_ordering v) SROOK_NOEXCEPT_TRUE                                                    \
    {                                                                                                                                       \
        return v.is_ordered && 0 OP v.value;                                                                                                \
    }
    DEF_RELOP(==)
    DEF_RELOP(<)
    DEF_RELOP(<=)
    DEF_RELOP(>)
    DEF_RELOP(>=)
#undef DEF_RELOP

    SROOK_CONSTEXPR operator weak_equality() const SROOK_NOEXCEPT_TRUE
    {
        return !value ? weak_equality::equivalent : weak_equality::nonequivalent;
    }
};

SROOK_INLINE_VARIABLE SROOK_CONSTEXPR partial_ordering partial_ordering::less(ord::less);
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR partial_ordering partial_ordering::equivalent(eq::equivalent);
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR partial_ordering partial_ordering::greater(ord::greater);
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR partial_ordering partial_ordering::unordered(ncmp::unordered);

#endif

SROOK_INLINE_NAMESPACE_END
} // namespace comparison
} // namespace srook

#endif
