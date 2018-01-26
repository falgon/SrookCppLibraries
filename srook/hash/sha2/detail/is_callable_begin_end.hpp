// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_HASH_SHA_DETAIL_IS_CALLABLE_BEGIN_END_HPP
#define INCLUDED_SROOK_HASH_SHA_DETAIL_IS_CALLABLE_BEGIN_END_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/type_traits/detail/sfinae_types.hpp>
#include <srook/utility/declval.hpp>

SROOK_NESTED_NAMESPACE(srook, hash) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T>
struct is_callable_begin_end : protected type_traits::detail::sfinae_types {
    static one test(SROOK_DEDUCED_TYPENAME T::const_iterator, SROOK_DEDUCED_TYPENAME T::const_iterator);
    static two test(...);
    static SROOK_CONSTEXPR bool value = sizeof(test(declval<T>().cbegin(), declval<T>().cend())) == sizeof(one);
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(hash, srook)

#endif
