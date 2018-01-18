// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_HASH_MURMUR3_DETAIL_MURMUR3_IMPL_HPP
#define INCLUDED_SROOK_HASH_MURMUR3_DETAIL_MURMUR3_IMPL_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/hash/murmur3/detail/murmur3_traits.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/is_character.hpp>
#include <srook/type_traits/remove_pointer.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/type_traits/detail/logical.hpp>

SROOK_NESTED_NAMESPACE(srook, hash) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <typename CharType, typename Integral>
class murmur3_calc {
    typedef murmur3_traits<sizeof(Integral)> traits;
public:
    SROOK_CONSTEXPR murmur3_calc(const CharType* s, std::size_t len, Integral seed)
        : hash_value(murmur3_impl1(murmur3_impl2(s + ((len >> 2) * sizeof(Integral)), len & 3, murmur3_impl3(s, len >> 2, seed)), len))
    {}
    SROOK_CONSTEXPR Integral operator()() const { return hash_value; }
private: // murmur3_impl3
    SROOK_CONSTEXPR Integral murmur3_impl3_5(Integral hash)
    {
        return (hash * traits::m) + traits::n;
    }
    SROOK_CONSTEXPR Integral murmur3_impl3_4(Integral hash)
    {
        return murmur3_impl3_5((hash << traits::r2a) | (hash >> traits::r2b));
    }
    SROOK_CONSTEXPR Integral murmur3_impl3_3(Integral key, Integral hash)
    {
        return murmur3_impl3_4(hash ^ key);
    }
    SROOK_CONSTEXPR Integral murmur3_impl3_2(Integral key, Integral hash)
    {
        return murmur3_impl3_3(key * traits::c2, hash);
    }
    SROOK_CONSTEXPR Integral murmur3_impl3_1(Integral key, Integral hash)
    {
        return murmur3_impl3_2((key << traits::r1a) | (key >> traits::r1b), hash);
    }
    SROOK_CONSTEXPR Integral murmur3_impl3_0(Integral key, Integral hash)
    {
        return murmur3_impl3_1(key * traits::c1, hash);
    }
    SROOK_CONSTEXPR Integral murmur3_impl3(const CharType* key, std::size_t len, Integral hash)
    {
        return len ? murmur3_impl3(key + sizeof(Integral), len - 1, murmur3_impl3_0(traits::reap(key), hash)) : hash;
    }
private: // murmur3_impl2
    SROOK_CONSTEXPR Integral murmur3_impl2_3(Integral key, Integral hash)
    {
        return hash ^ key;
    }
    SROOK_CONSTEXPR Integral murmur3_impl2_2(Integral key, Integral hash)
    {
        return murmur3_impl2_3(key * traits::c2, hash);
    }
    SROOK_CONSTEXPR Integral murmur3_impl2_1(Integral key, Integral hash)
    {
        return murmur3_impl2_2((key << traits::r1a) | (key >> traits::r1b), hash);
    }
    SROOK_CONSTEXPR Integral murmur3_impl2_0(Integral key, Integral hash)
    {
        return murmur3_impl2_1(key * traits::c1, hash);
    }
    SROOK_CONSTEXPR Integral murmur3_impl2(const CharType* key, std::size_t len, Integral hash)
    {
        return len ? murmur3_impl2_0(traits::reap(key, len), hash) : hash;
    }

private: // murmur3_impl1
    SROOK_CONSTEXPR Integral murmur3_impl1_4(Integral hash)
    {
        return hash ^ (hash >> traits::last_shift);
    }
    SROOK_CONSTEXPR Integral murmur3_impl1_3(Integral hash)
    {
        return murmur3_impl1_4(hash * traits::second_mul);
    }
    SROOK_CONSTEXPR Integral murmur3_impl1_2(Integral hash)
    {
        return murmur3_impl1_3(hash ^ (hash >> traits::second_shift));
    }
    SROOK_CONSTEXPR Integral murmur3_impl1_1(Integral hash)
    {
        return murmur3_impl1_2(hash * traits::first_mul);
    }
    SROOK_CONSTEXPR Integral murmur3_impl1_0(Integral hash)
    {
        return murmur3_impl1_1(hash ^ (hash >> traits::first_shift));
    }
    SROOK_CONSTEXPR Integral murmur3_impl1(Integral hash, std::size_t len)
    {
        return murmur3_impl1_0(hash ^ len);
    }

private:
    Integral hash_value;
};
    
    
 template <typename Integral, typename CharType>   
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<is_character<SROOK_DEDUCED_TYPENAME decay<CharType>::type>::value, Integral>::type
murmur3_impl(const CharType* s, std::size_t len, Integral seed)
{
    return murmur3_calc<CharType, Integral>(s, len, seed)();
}

template <typename Integral, class String>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
enable_if<
    type_traits::detail::Lnot<
        is_character<SROOK_DEDUCED_TYPENAME remove_cv<SROOK_DEDUCED_TYPENAME remove_pointer<String>::type>::type>
    >::value, Integral
>::type
murmur3_impl(String s, std::size_t len, Integral seed)
{
    return murmur3_impl(s.data(), len, seed);
}

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(hash, srook)

#endif
