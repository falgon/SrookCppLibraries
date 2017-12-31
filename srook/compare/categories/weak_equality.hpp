// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_COMPARE_CATEGORIES_WEAK_EQUALITY_HPP
#define INCLUDED_SROOK_COMPARE_CATEGORIES_WEAK_EQUALITY_HPP

#include <srook/config.hpp>
#include <srook/utility.hpp>
#include <srook/compare/categories/exposition_values.hpp>

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

class weak_equality : protected std::weak_equality {
    typedef std::weak_equality base_type;
public:
    using base_type::base_type;
    using base_type::equivalent;
    using base_type::nonequivalent;
    using base_type::operator==;
    using base_type::operator!=;
};

#else

class weak_equality {
    int value;
    explicit SROOK_CONSTEXPR weak_equality(eq v) : value(int(v)) {}
public:
    static const weak_equality equivalent;
    static const weak_equality nonequivalent;

    template <class U, SROOK_REQUIRES(type_traits::detail::Lnot<is_same<weak_equality, SROOK_DEDUCED_TYPENAME decay<U>::type>>::value)>
    friend SROOK_CONSTEXPR bool operator==(weak_equality v, U&&) SROOK_NOEXCEPT_TRUE { return v.value == 0; }
    template <class U, SROOK_REQUIRES(type_traits::detail::Lnot<is_same<weak_equality, SROOK_DEDUCED_TYPENAME decay<U>::type>>::value)>
    friend SROOK_CONSTEXPR bool operator==(U&& l, weak_equality v) SROOK_NOEXCEPT_TRUE { return v == srook::forward<U>(l); }
    template <class U, SROOK_REQUIRES(type_traits::detail::Lnot<is_same<weak_equality, SROOK_DEDUCED_TYPENAME decay<U>::type>>::value)>
    friend SROOK_CONSTEXPR bool operator!=(weak_equality v, U&& r) SROOK_NOEXCEPT_TRUE { return !(v == r); }
    template <class U, SROOK_REQUIRES(type_traits::detail::Lnot<is_same<weak_equality, SROOK_DEDUCED_TYPENAME decay<U>::type>>::value)>
    friend SROOK_CONSTEXPR bool operator!=(U&& l, weak_equality v) SROOK_NOEXCEPT_TRUE { return v != l; }
};

SROOK_INLINE_VARIABLE SROOK_CONSTEXPR weak_equality weak_equality::equivalent(eq::equivalent);
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR weak_equality weak_equality::nonequivalent(eq::nonequivalent);

#endif

SROOK_INLINE_NAMESPACE_END
} // namespace comparison
} // namespace srook

#endif
