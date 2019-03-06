// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_HASH_SHA2_HASH_CONCEPT_STYLE_HPP
#define INCLUDED_SROOK_HASH_SHA2_HASH_CONCEPT_STYLE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/hash/sha2/sha2_impl.hpp>
#include <srook/string/to_string.hpp>
#include <srook/type_traits/library_concepts/Hash.hpp>

SROOK_NESTED_NAMESPACE(srook, hash) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, std::size_t x, std::size_t y, class Iter, bool = is_range<T>::value>
struct sha2_hash_impl {
    typedef T argument_type;
    typedef std::size_t result_type;

    SROOK_FORCE_INLINE result_type operator()(const argument_type& s) const
    {
        return std::hash<std::string>()(srook::hash::sha2<x, y, Iter>(srook::begin(s), srook::end(s)).str());
    }
};

template <class T, std::size_t x, std::size_t y, class Iter>
struct sha2_hash_impl<T, x, y, Iter, false> {
    typedef T argument_type;
    typedef std::size_t result_type;

    SROOK_FORCE_INLINE result_type operator()(const argument_type& s) const
    {
        return std::hash<std::string>()(srook::hash::sha2<x, y, Iter>(srook::to_string(s)).str());
    }
};

} // namespace detail

template <class T, std::size_t x, std::size_t y = 0, class Iter = std::string::const_iterator>
struct sha2_hash : srook::hash::detail::sha2_hash_impl<T, x, y, Iter> {
    SROOK_ST_ASSERT(is_hash<srook::hash::detail::sha2_hash_impl<T, x, y, Iter>>::value);
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(hash, srook)
#endif
