// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CSTDDEF_BYTE_HPP
#define INCLUDED_SROOK_CSTDDEF_BYTE_HPP
#include<srook/config/require.hpp>
#include<type_traits>

namespace srook{

enum class byte : unsigned char {};

namespace literals{
namespace byte_literals{

byte operator"" _byte(unsigned long long b)
{
	return byte(b);
}

} // namespace byte_literals
} // namespace literals

template<class IntegerType,REQUIRES(std::is_integral<IntegerType>::value)>
constexpr IntegerType to_integer(byte b)noexcept
{
	return IntegerType(b);
}

template<class IntegerType,REQUIRES(std::is_integral<IntegerType>::value)>
constexpr byte& operator<<=(byte& b,IntegerType shift)noexcept
{
	return b = byte(static_cast<typename std::underlying_type<byte>::type>(b) << shift);
}

template <class IntegerType,REQUIRES(std::is_integral<IntegerType>::value)>
constexpr byte& operator>>=(byte& b,IntegerType shift)noexcept
{
	return b = byte(static_cast<typename std::underlying_type<byte>::type>(b) >> shift);
}

template <class IntegerType,REQUIRES(std::is_integral<IntegerType>::value)>
constexpr byte operator<<(byte b,IntegerType shift)noexcept
{
	return byte(static_cast<typename std::underlying_type<byte>::type>(b) << shift);
}

template <class IntegerType,REQUIRES(std::is_integral<IntegerType>::value)>
constexpr byte operator>>(byte b,IntegerType shift)noexcept
{
	return byte(static_cast<typename std::underlying_type<byte>::type>(b) >> shift);
}

constexpr byte& operator|=(byte& l,byte r)noexcept
{
	return l = byte(static_cast<typename std::underlying_type<byte>::type>(l) | static_cast<typename std::underlying_type<byte>::type>(r));
}
	
constexpr byte& operator&=(byte& l,byte r)noexcept
{
	return l = byte(static_cast<typename std::underlying_type<byte>::type>(l) & static_cast<typename std::underlying_type<byte>::type>(r));
}

constexpr byte& operator^=(byte& l,byte r) noexcept
{
	return l = byte(static_cast<typename std::underlying_type<byte>::type>(l) ^ static_cast<typename std::underlying_type<byte>::type>(r));
}

constexpr byte operator|(byte l, byte r) noexcept
{
	return byte(static_cast<typename std::underlying_type<byte>::type>(l) | static_cast<typename std::underlying_type<byte>::type>(r));
}

constexpr byte operator&(byte l, byte r) noexcept
{
	return byte(static_cast<typename std::underlying_type<byte>::type>(l) & static_cast<typename std::underlying_type<byte>::type>(r));
}

constexpr byte operator^(byte l, byte r) noexcept
{
	return byte(static_cast<typename std::underlying_type<byte>::type>(l) ^ static_cast<typename std::underlying_type<byte>::type>(r));
}

constexpr byte operator~(byte b) noexcept
{
	return byte(~static_cast<typename std::underlying_type<byte>::type>(b));
}

} // namespace srook

#endif
