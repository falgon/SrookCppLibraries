// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_BYTE_HPP
#define INCLUDED_SROOK_CONFIG_BYTE_HPP

namespace srook{

enum class byte:unsigned char{};

template<class IntegerType>
constexpr IntegerType to_integer(byte b)noexcept
{
	return IntegerType(b);
}

template<class IntegerType>
constexpr byte& operator<<=(byte& b,IntegerType shift)noexcept
{
	return b=byte(static_cast<unsigned char>(b) << shift);
}

template <class IntegerType>
constexpr byte& operator>>=(byte& b,IntegerType shift)noexcept
{
	return b=byte(static_cast<unsigned char>(b) >> shift);
}

template <class IntegerType>
constexpr byte operator<<(byte b,IntegerType shift)noexcept
{
	return byte(static_cast<unsigned char>(b) << shift);
}

template <class IntegerType>
constexpr byte operator>>(byte b,IntegerType shift)noexcept
{
	return byte(static_cast<unsigned char>(b) >> shift);
}

constexpr byte& operator|=(byte& l,byte r)noexcept
{
	return l = byte(static_cast<unsigned char>(l) | static_cast<unsigned char>(r));
}
	
constexpr byte& operator&=(byte& l,byte r)noexcept
{
	return l = byte(static_cast<unsigned char>(l) & static_cast<unsigned char>(r));
}

constexpr byte& operator^=(byte& l,byte r) noexcept
{
	return l = byte(static_cast<unsigned char>(l) ^ static_cast<unsigned char>(r));
}

constexpr byte operator|(byte l, byte r) noexcept
{
	return byte(static_cast<unsigned char>(l) | static_cast<unsigned char>(r));
}

constexpr byte operator&(byte l, byte r) noexcept
{
	return byte(static_cast<unsigned char>(l) & static_cast<unsigned char>(r));
}

constexpr byte operator^(byte l, byte r) noexcept
{
	return byte(static_cast<unsigned char>(l) ^ static_cast<unsigned char>(r));
}

constexpr byte operator~(byte b) noexcept
{
	return byte(~static_cast<unsigned char>(b));
}

} // namespace srook

#endif
