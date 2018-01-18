// Copyrsght (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_HASH_MURMUR3_DETAIL_MURMUR3_TRAITS_HPP
#define INCLUDED_SROOK_HASH_MURMUR3_DETAIL_MURMUR3_TRAITS_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/cstdint.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/is_character.hpp>
#include <srook/type_traits/remove_reference.hpp>

SROOK_NESTED_NAMESPACE(srook, hash) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t>
struct murmur3_traits;

// Naming convention ref: https://en.wikipedia.org/wiki/MurmurHash
template<>
struct murmur3_traits<4> {
    typedef srook::uint32_t value_type;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST value_type c1 = 0xcc9e2d51;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST value_type c2 = 0x1b873593;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST value_type r1a = 15;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST value_type r1b = 17;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST value_type r2a = 13;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST value_type r2b = 19;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST value_type m = 5;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST value_type n = 0xe6546b64;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST value_type first_shift = 16;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST value_type first_mul = 0x85ebca6b;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST value_type second_shift = 13;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST value_type second_mul = 0xc2b2ae35;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST value_type last_shift = first_shift;
    template <typename CharType>
    static SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
    enable_if<is_character<SROOK_DEDUCED_TYPENAME remove_reference<CharType>::type>::value, value_type>::type
    reap(const CharType* key, std::size_t len = sizeof(value_type), value_type hash = 0)
    {
        return len ? reap(key, len - 1, (hash << 8) | *(key + (len - 1))) : hash;
    }
};

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(hash, srook)

#endif
