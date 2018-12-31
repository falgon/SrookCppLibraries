// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CSTDDEF_BYTE_HPP
#define INCLUDED_SROOK_CSTDDEF_BYTE_HPP
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature.hpp>
#include <srook/config/require.hpp>
#include <srook/type_traits/underlying_type.hpp>

namespace srook {

enum class byte : unsigned char {};

namespace literals {
namespace byte_literals {

SROOK_CONSTEXPR byte operator"" _byte(unsigned long long b)
{
    return byte(b);
}

} // namespace byte_literals
} // namespace literals

template <class IntegerType, REQUIRES(std::is_integral<IntegerType>::value)>
SROOK_CONSTEXPR IntegerType to_integer(byte b) SROOK_NOEXCEPT_TRUE
{
    return IntegerType(b);
}
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
SROOK_CONSTEXPR std::byte to_stdbyte(byte b) SROOK_NOEXCEPT_TRUE
{
    return std::byte(static_cast<typename srook::underlying_type<byte>::type>(b));
}
#endif

SROOK_CONSTEXPR byte operator+(const byte& l, const byte& r)
{
    return byte(static_cast<typename srook::underlying_type<byte>::type>(l) + static_cast<typename srook::underlying_type<byte>::type>(r));
}
template <class Value>
SROOK_CONSTEXPR Value operator+(byte l, Value v)
{
    return static_cast<Value>(l) + v;
}
template <class Value>
SROOK_CONSTEXPR Value operator+(Value v, byte l)
{
    return static_cast<Value>(v) + l;
}

SROOK_CONSTEXPR byte operator-(const byte& l, const byte& r)
{
    return byte(static_cast<typename srook::underlying_type<byte>::type>(l) - static_cast<typename srook::underlying_type<byte>::type>(r));
}
SROOK_CONSTEXPR byte operator*(const byte& l, const byte& r)
{
    return byte(static_cast<typename srook::underlying_type<byte>::type>(l) * static_cast<typename srook::underlying_type<byte>::type>(r));
}
SROOK_CONSTEXPR byte operator/(const byte& l, const byte& r)
{
    return byte(static_cast<typename srook::underlying_type<byte>::type>(l) / static_cast<typename srook::underlying_type<byte>::type>(r));
}

template <class IntegerType, REQUIRES(std::is_integral<IntegerType>::value)>
SROOK_CONSTEXPR byte& operator<<=(byte& b, IntegerType shift) SROOK_NOEXCEPT_TRUE
{
    return b = byte(static_cast<typename srook::underlying_type<byte>::type>(b) << shift);
}

template <class IntegerType, REQUIRES(std::is_integral<IntegerType>::value)>
SROOK_CONSTEXPR byte& operator>>=(byte& b, IntegerType shift) SROOK_NOEXCEPT_TRUE
{
    return b = byte(static_cast<typename srook::underlying_type<byte>::type>(b) >> shift);
}

template <class IntegerType, REQUIRES(std::is_integral<IntegerType>::value)>
SROOK_CONSTEXPR byte operator<<(byte b, IntegerType shift) SROOK_NOEXCEPT_TRUE
{
    return byte(static_cast<typename srook::underlying_type<byte>::type>(b) << shift);
}

template <class IntegerType, REQUIRES(std::is_integral<IntegerType>::value)>
SROOK_CONSTEXPR byte operator>>(byte b, IntegerType shift) SROOK_NOEXCEPT_TRUE
{
    return byte(static_cast<typename srook::underlying_type<byte>::type>(b) >> shift);
}

SROOK_CXX14_CONSTEXPR byte& operator|=(byte& l, byte r) SROOK_NOEXCEPT_TRUE
{
    return l = byte(static_cast<typename srook::underlying_type<byte>::type>(l) | static_cast<typename srook::underlying_type<byte>::type>(r));
}

SROOK_CXX14_CONSTEXPR byte& operator&=(byte& l, byte r) SROOK_NOEXCEPT_TRUE
{
    return l = byte(static_cast<typename srook::underlying_type<byte>::type>(l) & static_cast<typename srook::underlying_type<byte>::type>(r));
}

SROOK_CXX14_CONSTEXPR byte& operator^=(byte& l, byte r) SROOK_NOEXCEPT_TRUE
{
    return l = byte(static_cast<typename srook::underlying_type<byte>::type>(l) ^ static_cast<typename srook::underlying_type<byte>::type>(r));
}

SROOK_CONSTEXPR byte operator|(byte l, byte r) SROOK_NOEXCEPT_TRUE
{
    return byte(static_cast<typename srook::underlying_type<byte>::type>(l) | static_cast<typename srook::underlying_type<byte>::type>(r));
}

SROOK_CONSTEXPR byte operator&(byte l, byte r)SROOK_NOEXCEPT_TRUE
{
    return byte(static_cast<typename srook::underlying_type<byte>::type>(l) & static_cast<typename srook::underlying_type<byte>::type>(r));
}

SROOK_CONSTEXPR byte operator^(byte l, byte r) SROOK_NOEXCEPT_TRUE
{
    return byte(static_cast<typename srook::underlying_type<byte>::type>(l) ^ static_cast<typename srook::underlying_type<byte>::type>(r));
}

SROOK_CONSTEXPR byte operator~(byte b)SROOK_NOEXCEPT_TRUE
{
    return byte(~static_cast<typename srook::underlying_type<byte>::type>(b));
}

} // namespace srook

#endif
