// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_HASH_SHA_DETAIL_SHAX_UTIL_HPP
#define INCLUDED_SROOK_HASH_SHA_DETAIL_SHAX_UTIL_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/cxx20/concepts/iterator/InputIterator.hpp>
#include <srook/hash/sha2/detail/config.hpp>
#include <srook/hash/sha2/detail/sum.hpp>
#include <srook/type_traits/is_character.hpp>
#include <srook/type_traits/remove_extent.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/algorithm/rotate.hpp>
#include <srook/iterator/range_access.hpp>
#include <cassert>

SROOK_NESTED_NAMESPACE(srook, hash) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
class sha2_util_core {
protected:
    typedef T sum_type;
    typedef SROOK_DEDUCED_TYPENAME sum_type::value_type value_type;
    static SROOK_CONSTEXPR sum_type sum(const sum_type& l, const sum_type& r) { return detail::sum(l, r); }
    template <class Integral>
    static SROOK_CONSTEXPR sum_type& rotate(sum_type& s, const Integral& t1, const Integral& t2)
    {
        typedef std::reverse_iterator<SROOK_DEDUCED_TYPENAME sum_type::iterator> riter;
        srook::algorithm::rotate(riter(srook::end(s)), std::next(riter(srook::end(s)), 1), riter(srook::begin(s)));
        s[s.size() / 2] += t1;
        s[0] = t1 + t2;
        return s;
    }
    
    // The right shift operation
    static SROOK_CONSTEXPR value_type SHFR(value_type x, value_type n) 
    { 
        assert(n < sizeof(value_type) * CHAR_BIT);
        return x >> n; 
    }

    // The rotate right (circular right shift) operation
    static SROOK_CONSTEXPR value_type ROTR(value_type x, value_type n) 
    {
        assert(n < sizeof(value_type) * CHAR_BIT);
        return (x >> n) | (x << ((sizeof(x) << 3) - n)); 
    }

    // The rotate left (circular left shift) operation
    static SROOK_CONSTEXPR value_type ROTL(value_type x, value_type n) 
    { 
        return (x << n) | (x >> ((sizeof(x) << 3) - n)); 
    }

    // The function `Ch` that described by FIPS 180-4 4.1 Functions
    static SROOK_CONSTEXPR value_type Ch(value_type x, value_type y, value_type z) 
    { 
        return (x & y) ^ (~x & z); 
    }

    // The function 'Maj' that described by FIPS 180-4 4.1 Functions
    static SROOK_CONSTEXPR value_type Maj(value_type x, value_type y, value_type z) 
    { 
        return (x & y) ^ (x & z) ^ (y & z); 
    }
};

template <class, std::size_t>
class sha2_util;

template <class T>
class sha2_util<T, 4> : protected sha2_util_core<T> {
    typedef sha2_util_core<T> base_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::sum_type sum_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::value_type value_type;
    SROOK_ST_ASSERT((is_same<value_type, srook::uint32_t>::value));

#if SROOK_HAS_CONCEPTS
    template <srook::concepts::InputIterator InputIter>
#else
    template <typename InputIter>
#endif
    static SROOK_CXX14_CONSTEXPR InputIter
    unpack_impl(value_type x, InputIter iter, std::size_t pos = 2, std::size_t bit = CHAR_BIT)
    {
        return 
            !pos ? (*iter = static_cast<srook::uint8_t>(x >> bit), iter)
            : unpack_impl(x, (*std::next(iter, pos) = static_cast<srook::uint8_t>(x >> bit), iter), pos - 1, bit + CHAR_BIT);
    }
protected:
    using base_type::sum;
    using base_type::SHFR;
    using base_type::ROTR;
    using base_type::ROTL;
    using base_type::Ch;
    using base_type::Maj;
    using base_type::rotate;
    
#if SROOK_HAS_CONCEPTS
    template <srook::concepts::InputIterator InputIter>
#else
    template <typename InputIter>
#endif
    static SROOK_CXX14_CONSTEXPR value_type&
    pack(InputIter iter, value_type& x)
    {
        return
            x = static_cast<value_type>(*std::next(iter, 3))
            | (static_cast<value_type>(*std::next(iter, 2)) << CHAR_BIT)
            | (static_cast<value_type>(*std::next(iter, 1)) << CHAR_BIT * 2)
            | (static_cast<value_type>(*iter) << CHAR_BIT * 3);
    }
#if SROOK_HAS_CONCEPTS
    template <srook::concepts::InputIterator InputIter>
#else
    template <typename InputIter>
#endif
    static SROOK_CXX14_CONSTEXPR InputIter
    unpack1(value_type x, InputIter iter)
    {
        return unpack_impl(x, (*std::next(iter, 3) = static_cast<srook::uint8_t>(x), iter));
    }
#if SROOK_HAS_CONCEPTS
    template <srook::concepts::InputIterator InputIter>
#else
    template <typename InputIter>
#endif
    static SROOK_CXX14_CONSTEXPR InputIter
    unpack2(value_type x, InputIter iter)
    {
        return unpack1(x, iter);
    }

    struct s_4_1 {
        static SROOK_CONSTEXPR value_type f_1(value_type x) { return ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22); }
        static SROOK_CONSTEXPR value_type f_2(value_type x) { return ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25); }
        static SROOK_CONSTEXPR value_type f_3(value_type x) { return ROTR(x, 7) ^ ROTR(x, 18) ^ SHFR(x, 3); }
        static SROOK_CONSTEXPR value_type f_4(value_type x) { return ROTR(x, 17) ^ ROTR(x, 19) ^ SHFR(x, 10); }
    };

    template <class U, std::size_t n>
    static SROOK_CONSTEXPR srook::array<U, n>& SCR(srook::array<U, n>& s, std::size_t i)
    {
        return (s[i] = s_4_1::f_4(s[i - 2]) + s[i - 7] + s_4_1::f_3(s[i - 15]) + s[i - 16], s);
    }
};

template <class T>
class sha2_util<T, 8> : protected sha2_util_core<T> {
    typedef sha2_util_core<T> base_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::sum_type sum_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::value_type value_type;
    
#if SROOK_HAS_CONCEPTS
    template <srook::concepts::InputIterator InputIter>
#else
    template <typename InputIter>
#endif
    static SROOK_CXX14_CONSTEXPR InputIter
    unpack_impl(value_type x, InputIter iter, std::size_t pos = 6, std::size_t bit = CHAR_BIT)
    {
        return 
            !pos ? (*iter = static_cast<srook::uint8_t>(x >> bit), iter)
            : unpack_impl(x, (*std::next(iter, pos) = static_cast<srook::uint8_t>(x >> bit), iter), pos - 1, bit + CHAR_BIT);
    }
#if SROOK_HAS_CONCEPTS
    template <srook::concepts::InputIterator InputIter>
#else
    template <typename InputIter>
#endif
    static SROOK_CXX14_CONSTEXPR InputIter
    unpack_impl2(value_type x, InputIter iter, std::size_t pos = 2, std::size_t bit = CHAR_BIT)
    {
        return 
            !pos ? (*iter = static_cast<srook::uint8_t>(x >> bit), iter)
            : unpack_impl2(x, (*std::next(iter, pos) = static_cast<srook::uint8_t>(x >> bit), iter), pos - 1, bit + CHAR_BIT);
    }
protected:
    using base_type::sum;
    using base_type::SHFR;
    using base_type::ROTR;
    using base_type::ROTL;
    using base_type::Ch;
    using base_type::Maj;
    using base_type::rotate;

#if SROOK_HAS_CONCEPTS
    template <srook::concepts::InputIterator InputIter>
#else
    template <typename InputIter>
#endif
    static SROOK_CONSTEXPR value_type&
    pack(InputIter s, value_type& x)
    {
        return 
            x = static_cast<value_type>(*std::next(s, 7)) 
            | (static_cast<value_type>(*std::next(s, 6)) << 8) 
            | (static_cast<value_type>(*std::next(s, 5)) << 16) 
            | (static_cast<value_type>(*std::next(s, 4)) << 24) 
            | (static_cast<value_type>(*std::next(s, 3)) << 32) 
            | (static_cast<value_type>(*std::next(s, 2)) << 40) 
            | (static_cast<value_type>(*std::next(s, 1)) << 48) 
            | (static_cast<value_type>(*s) << 56);
    }
#if SROOK_HAS_CONCEPTS
    template <srook::concepts::InputIterator InputIter>
#else
    template <typename InputIter>
#endif
    static SROOK_CONSTEXPR InputIter
    unpack1(value_type x, InputIter s)
    {
        return unpack_impl(x, (*std::next(s, 7) = static_cast<srook::uint8_t>(x), s));
    }
#if SROOK_HAS_CONCEPTS
    template <srook::concepts::InputIterator InputIter>
#else
    template <typename InputIter>
#endif
    static SROOK_CONSTEXPR InputIter
    unpack2(value_type x, InputIter iter)
    {
        return unpack_impl2(x, (*std::next(iter, 3) = static_cast<srook::uint8_t>(x), iter));
    }

    struct s_4_1 {
        static SROOK_CONSTEXPR value_type f_1(value_type x) { return ROTR(x, 28) ^ ROTR(x, 34) ^ ROTR(x, 39); }
        static SROOK_CONSTEXPR value_type f_2(value_type x) { return ROTR(x, 14) ^ ROTR(x, 18) ^ ROTR(x, 41); }
        static SROOK_CONSTEXPR value_type f_3(value_type x) { return ROTR(x, 1) ^ ROTR(x, 8) ^ SHFR(x, 7); }
        static SROOK_CONSTEXPR value_type f_4(value_type x) { return ROTR(x, 19) ^ ROTR(x, 61) ^ SHFR(x, 6); }
    };

    template <class U, std::size_t n>
    static SROOK_CONSTEXPR srook::array<U, n>& SCR(srook::array<U, n>& s, std::size_t i)
    {
        return (s[i] = s_4_1::f_4(s[i - 2]) + s[i - 7] + s_4_1::f_3(s[i - 15]) + s[i - 16], s);
    }
};

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(hash, srook)

#endif
