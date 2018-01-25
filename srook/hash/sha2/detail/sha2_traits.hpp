// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_HASH_SHA_DETAIL_SHAX_TRAITS_HPP
#define INCLUDED_SROOK_HASH_SHA_DETAIL_SHAX_TRAITS_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/array.hpp>
#include <srook/hash/sha2/detail/sha2_util.hpp>

SROOK_NESTED_NAMESPACE(srook, hash) {
SROOK_INLINE_NAMESPACE(v1)

template <std::size_t, std::size_t = 0>
class sha2_traits;

template <>
class sha2_traits<512, 224> : protected detail::sha2_util<srook::array<srook::uint64_t, CHAR_BIT>, sizeof(srook::uint64_t)> {
public:
    typedef srook::uint64_t value_type;
    typedef srook::array<value_type, CHAR_BIT> sum_type;
private:
    typedef sha2_util<sum_type, sizeof(value_type)> base_type;
public:
    static SROOK_CONSTEXPR std::size_t disone_bit = CHAR_BIT;
    static SROOK_CONSTEXPR std::size_t subblock_shift = 3;
    static SROOK_CONSTEXPR std::size_t message_shift = 7;
    static SROOK_CONSTEXPR std::size_t k_size = srook::hash::detail::k_64.size();
    static SROOK_CONSTEXPR srook::array<value_type, k_size> round_constant = srook::hash::detail::k_64;
    static SROOK_CONSTEXPR srook::array<value_type, CHAR_BIT> init_hash = {
        0x8C3D37C819544DA2, 0x73E1996689DCD4D6, 0x1DFAB7AE32FF9C82, 0x679DD514582F9FCF,
        0x0F6D2B697BD44DA8, 0x77E36F7304C48942, 0x3F9D85A86A1D36C8, 0x1112E6AD91D692A1
    };
#ifdef SROOK_HAS_BOOST_MP_CPP_INT_HPP
    static const boost::multiprecision::uint128_t message_size;
#endif
    static SROOK_CONSTEXPR std::size_t block_size = detail::sha512_224_block_size;
    static SROOK_CONSTEXPR std::size_t message_digest_size = detail::sha512_224_message_digest_size;
    static SROOK_CONSTEXPR std::size_t last_unpack_distance = 4;

    using base_type::rotate;
    using base_type::sum;
    using base_type::SHFR;
    using base_type::ROTR;
    using base_type::ROTL;
    using base_type::Ch;
    using base_type::Maj;
    using base_type::pack;
    using base_type::unpack1;
    using base_type::unpack2;
    using base_type::s_4_1;
    using base_type::SCR;
};
#ifdef SROOK_HAS_BOOST_MP_CPP_INT_HPP
const boost::multiprecision::uint128_t sha2_traits<512, 224>::message_size = detail::sha512_224_message_size;
#endif

template <>
class sha2_traits<512, 256> : protected detail::sha2_util<srook::array<srook::uint64_t, CHAR_BIT>, sizeof(srook::uint64_t)> {
public:
    typedef srook::uint64_t value_type;
    typedef srook::array<value_type, CHAR_BIT> sum_type;
private:
    typedef sha2_util<sum_type, sizeof(value_type)> base_type;
public:
    static SROOK_CONSTEXPR std::size_t disone_bit = CHAR_BIT;
    static SROOK_CONSTEXPR std::size_t subblock_shift = 3;
    static SROOK_CONSTEXPR std::size_t message_shift = 7;
    static SROOK_CONSTEXPR std::size_t k_size = srook::hash::detail::k_64.size();
    static SROOK_CONSTEXPR srook::array<value_type, k_size> round_constant = srook::hash::detail::k_64;
    static SROOK_CONSTEXPR srook::array<value_type, CHAR_BIT> init_hash = {
        0x22312194FC2BF72C, 0x9F555FA3C84C64C2, 0x2393B86B6F53B151, 0x963877195940EABD,
        0x96283EE2A88EFFE3, 0xBE5E1E2553863992, 0x2B0199FC2C85B8AA, 0x0EB72DDC81C52CA2
    };
#ifdef SROOK_HAS_BOOST_MP_CPP_INT_HPP
    static const boost::multiprecision::uint128_t message_size;
#endif
    static SROOK_CONSTEXPR std::size_t block_size = detail::sha512_256_block_size;
    static SROOK_CONSTEXPR std::size_t message_digest_size = detail::sha512_256_message_digest_size;
    static SROOK_CONSTEXPR std::size_t last_unpack_distance = 4;
    
    using base_type::rotate;
    using base_type::sum;
    using base_type::SHFR;
    using base_type::ROTR;
    using base_type::ROTL;
    using base_type::Ch;
    using base_type::Maj;
    using base_type::pack;
    using base_type::unpack1;
    using base_type::unpack2;
    using base_type::s_4_1;
    using base_type::SCR;
};
#ifdef SROOK_HAS_BOOST_MP_CPP_INT_HPP
const boost::multiprecision::uint128_t sha2_traits<512, 256>::message_size = detail::sha512_256_message_size;
#endif

template <>
class sha2_traits<224, 0> : protected detail::sha2_util<srook::array<srook::uint32_t, CHAR_BIT>, sizeof(srook::uint32_t)> {
public:
    typedef srook::uint32_t value_type;
    typedef srook::array<value_type, CHAR_BIT> sum_type;
private:
    typedef sha2_util<sum_type, sizeof(value_type)> base_type;
public:
    static SROOK_CONSTEXPR std::size_t disone_bit = 0;
    static SROOK_CONSTEXPR std::size_t subblock_shift = 2;
    static SROOK_CONSTEXPR std::size_t message_shift = 6;
    static SROOK_CONSTEXPR std::size_t k_size = srook::hash::detail::k_32.size();
    static SROOK_CONSTEXPR srook::array<value_type, k_size> round_constant = srook::hash::detail::k_32;
    static SROOK_CONSTEXPR srook::array<value_type, CHAR_BIT> init_hash = {
        0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939, 
        0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4
    };
    static SROOK_CONSTEXPR srook::uint64_t message_size = detail::sha224_message_size;
    static SROOK_CONSTEXPR std::size_t block_size = detail::sha224_block_size;
    static SROOK_CONSTEXPR std::size_t message_digest_size = detail::sha224_message_digest_size;
    static SROOK_CONSTEXPR std::size_t last_unpack_distance = 1;

    using base_type::rotate;
    using base_type::sum;
    using base_type::SHFR;
    using base_type::ROTR;
    using base_type::ROTL;
    using base_type::Ch;
    using base_type::Maj;
    using base_type::pack;
    using base_type::unpack1;
    using base_type::unpack2;
    using base_type::s_4_1;
    using base_type::SCR;
};

template <>
class sha2_traits<256, 0> : protected detail::sha2_util<srook::array<srook::uint32_t, CHAR_BIT>, sizeof(srook::uint32_t)> {
public:
    typedef srook::uint32_t value_type;
    typedef srook::array<value_type, CHAR_BIT> sum_type;
private:
    typedef sha2_util<sum_type, sizeof(value_type)> base_type;
public:
    static SROOK_CONSTEXPR std::size_t disone_bit = 0;
    static SROOK_CONSTEXPR std::size_t subblock_shift = 2;
    static SROOK_CONSTEXPR std::size_t message_shift = 6;
    static SROOK_CONSTEXPR std::size_t k_size = srook::hash::detail::k_32.size();
    static SROOK_CONSTEXPR srook::array<value_type, k_size> round_constant = srook::hash::detail::k_32;
    static SROOK_CONSTEXPR srook::array<value_type, CHAR_BIT> init_hash = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    static SROOK_CONSTEXPR srook::uint64_t message_size = detail::sha256_message_size;
    static SROOK_CONSTEXPR std::size_t block_size = detail::sha256_block_size;
    static SROOK_CONSTEXPR std::size_t message_digest_size = detail::sha256_message_digest_size;
    static SROOK_CONSTEXPR std::size_t last_unpack_distance = 0;

    using base_type::rotate;
    using base_type::sum;
    using base_type::SHFR;
    using base_type::ROTR;
    using base_type::ROTL;
    using base_type::Ch;
    using base_type::Maj;
    using base_type::pack;
    using base_type::unpack1;
    using base_type::unpack2;
    using base_type::s_4_1;
    using base_type::SCR;
};

template <>
class sha2_traits<384, 0> : protected detail::sha2_util<srook::array<srook::uint64_t, CHAR_BIT>, sizeof(srook::uint64_t)> {
public:
    typedef srook::uint64_t value_type;
    typedef srook::array<value_type, CHAR_BIT> sum_type;
private:
    typedef sha2_util<sum_type, sizeof(value_type)> base_type;
public:
    static SROOK_CONSTEXPR std::size_t disone_bit = CHAR_BIT;
    static SROOK_CONSTEXPR std::size_t subblock_shift = 3;
    static SROOK_CONSTEXPR std::size_t message_shift = 7;
    static SROOK_CONSTEXPR std::size_t k_size = srook::hash::detail::k_64.size();
    static SROOK_CONSTEXPR srook::array<value_type, k_size> round_constant = srook::hash::detail::k_64;
    static SROOK_CONSTEXPR srook::array<value_type, CHAR_BIT> init_hash = {
        0xcbbb9d5dc1059ed8, 0x629a292a367cd507, 0x9159015a3070dd17, 0x152fecd8f70e5939,
        0x67332667ffc00b31, 0x8eb44a8768581511, 0xdb0c2e0d64f98fa7, 0x47b5481dbefa4fa4
    };
#ifdef SROOK_HAS_BOOST_MP_CPP_INT_HPP
    static const boost::multiprecision::uint128_t message_size;
#endif
    static SROOK_CONSTEXPR std::size_t block_size = detail::sha384_block_size;
    static SROOK_CONSTEXPR std::size_t message_digest_size = detail::sha384_message_digest_size;
    static SROOK_CONSTEXPR std::size_t last_unpack_distance = 2;
    
    using base_type::rotate;
    using base_type::sum;
    using base_type::SHFR;
    using base_type::ROTR;
    using base_type::ROTL;
    using base_type::Ch;
    using base_type::Maj;
    using base_type::pack;
    using base_type::unpack1;
    using base_type::unpack2;
    using base_type::s_4_1;
    using base_type::SCR;
};
#ifdef SROOK_HAS_BOOST_MP_CPP_INT_HPP
const boost::multiprecision::uint128_t sha2_traits<384, 0>::message_size = detail::sha384_message_size;
#endif

template <>
class sha2_traits<512, 0> : protected detail::sha2_util<srook::array<srook::uint64_t, CHAR_BIT>, sizeof(srook::uint64_t)> {
public:
    typedef srook::uint64_t value_type;
    typedef srook::array<value_type, CHAR_BIT> sum_type;
private:
    typedef sha2_util<sum_type, sizeof(value_type)> base_type;
public:
    static SROOK_CONSTEXPR std::size_t disone_bit = CHAR_BIT;
    static SROOK_CONSTEXPR std::size_t subblock_shift = 3;
    static SROOK_CONSTEXPR std::size_t message_shift = 7;
    static SROOK_CONSTEXPR std::size_t k_size = srook::hash::detail::k_64.size();
    static SROOK_CONSTEXPR srook::array<value_type, k_size> round_constant = srook::hash::detail::k_64;
    static SROOK_CONSTEXPR srook::array<value_type, CHAR_BIT> init_hash = {
        0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1, 
        0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
    };
#ifdef SROOK_HAS_BOOST_MP_CPP_INT_HPP
    static const boost::multiprecision::uint128_t message_size;
#endif
    static SROOK_CONSTEXPR std::size_t block_size = detail::sha512_block_size;
    static SROOK_CONSTEXPR std::size_t message_digest_size = detail::sha512_message_digest_size;
    static SROOK_CONSTEXPR std::size_t last_unpack_distance = 0;
        
    using base_type::rotate;
    using base_type::sum;
    using base_type::SHFR;
    using base_type::ROTR;
    using base_type::ROTL;
    using base_type::Ch;
    using base_type::Maj;
    using base_type::pack;
    using base_type::unpack1;
    using base_type::unpack2;
    using base_type::s_4_1;
    using base_type::SCR;
};
#ifdef SROOK_HAS_BOOST_MP_CPP_INT_HPP
const boost::multiprecision::uint128_t sha2_traits<512, 0>::message_size = detail::sha512_message_size;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(hash, srook)

#endif
