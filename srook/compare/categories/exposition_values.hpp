// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_COMPARISON_CATEGORIES_EXPOSITION_VALUES_HPP
#define INCLUDED_SROOK_COMPARISON_CATEGORIES_EXPOSITION_VALUES_HPP

#include <srook/config.hpp>

namespace srook {
namespace comparison {
namespace categories {
SROOK_INLINE_NAMESPACE(v1)

SROOK_STRONG_ENUM_BEGIN(eq) {
    equal = 0, equivalent = equal, nonequal = 1, nonequivalent = nonequal
};
SROOK_STRONG_ENUM_EPILOG(eq)

SROOK_STRONG_ENUM_BEGIN(ord) {
    less = -1, greater = 1
};
SROOK_STRONG_ENUM_EPILOG(ord)

SROOK_STRONG_ENUM_BEGIN(ncmp) {
    unordered = -127
};
SROOK_STRONG_ENUM_EPILOG(ncmp)

SROOK_INLINE_NAMESPACE_END
} // namespace categories

using categories::eq;
using categories::ord;
using categories::ncmp;

} // namespace comparison
} // namespace srook

#endif
