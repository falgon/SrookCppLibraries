// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_UTILITY_LAMBDA_WRAPPER_HPP
#define INCLUDED_SROOK_UTILITY_LAMBDA_WRAPPER_HPP

#include <srook/iterator/range_iterators/detail/lambda_wrapper.hpp>

SROOK_NESTED_NAMESPACE(srook, utility) {
SROOK_INLINE_NAMESPACE(v1)

using srook::range::iterator::detail::lambda_wrapper;

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(utility, srook)

namespace srook {

using srook::utility::lambda_wrapper;

} // namespace srook

#endif
