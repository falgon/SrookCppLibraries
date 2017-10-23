// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_UTILITY_LG_HPP
#define INCLUDED_SROOK_UTILITY_LG_HPP

namespace srook{
namespace impl{

template<typename Size>
constexpr inline Size lg(Size n)
{
	return n ? 1 + lg(n >>= 1) : -1;
}

} // namespace impl
} // namespace srook 

#endif
