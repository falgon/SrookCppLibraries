// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_UTILITY_DUPE_HPP
#define INCLUDED_SROOK_TUPLE_UTILITY_DUPE_HPP

#include <srook/tuple/utility/detail/utils.hpp>

SROOK_NESTED_NAMESPACE(srook, tuple, utility) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
SROOK_CXX14_CONSTEXPR SROOK_FORCE_INLINE std::pair<T, T> 
dupe(T&& v) SROOK_NOEXCEPT_TRUE
{
    SROOK_DEDUCED_TYPENAME decay<T>::type first = v;
    return std::make_pair(srook::move(first), srook::forward<T>(v));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(utility, tuple, srook)
#endif
