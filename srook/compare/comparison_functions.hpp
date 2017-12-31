// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_COMPARE_COMPARISON_FUNCTIONS_HPP
#define INCLUDED_SROOK_COMPARE_COMPARISON_FUNCTIONS_HPP

#include <srook/compare/categories.hpp>

namespace srook {
namespace comparison {

SROOK_CONSTEXPR bool is_eq(weak_equality cmp) SROOK_NOEXCEPT_TRUE { return cmp == 0; }
SROOK_CONSTEXPR bool is_neq(weak_equality cmp) SROOK_NOEXCEPT_TRUE { return cmp != 0; }
SROOK_CONSTEXPR bool is_lt(partial_ordering cmp) SROOK_NOEXCEPT_TRUE { return cmp < 0; }
SROOK_CONSTEXPR bool is_lteq(partial_ordering cmp) SROOK_NOEXCEPT_TRUE { return cmp <= 0; }
SROOK_CONSTEXPR bool is_gt(partial_ordering cmp) SROOK_NOEXCEPT_TRUE { return cmp > 0; }
SROOK_CONSTEXPR bool is_gteq(partial_ordering cmp) SROOK_NOEXCEPT_TRUE { return cmp >= 0; }

} // namespace comparison
} // namespace srook

#endif
