// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_UTILITY_INDEX_SEQUENCE_HPP
#define INCLUDED_SROOK_UTILITY_INDEX_SEQUENCE_HPP
#include <cstddef>
#include <srook/config/feature/inline_namespace.hpp> 
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/noexcept_detection.hpp>

namespace srook{
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

template<std::size_t... v>
struct index_sequence{ // implementation for non-support alias templates
	typedef std::size_t value_type;
	static SROOK_CONSTEXPR value_type size() SROOK_NOEXCEPT_TRUE
	{ 
		return sizeof...(v); 
	}
};

SROOK_INLINE_NAMESPACE_END
} // namespace utility

using utility::index_sequence;

} // namespace srook

#endif
