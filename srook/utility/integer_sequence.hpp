#ifndef INCLUDED_SROOK_UTILITY_INTEGER_SEQUENCE_HPP
#define INCLUDED_SROOK_UTILITY_INTEGER_SEQUENCE_HPP
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <cstddef>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp> 
#include <srook/config/noexcept_detection.hpp>

namespace srook{
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

template<class T,T... v>
struct integer_sequence {
	using type = T;
	static SROOK_CONSTEXPR std::size_t size() SROOK_NOEXCEPT_TRUE { return sizeof...(v); }
};

SROOK_INLINE_NAMESPACE_END
} // namespace utility

using utility::integer_sequence;

} // namespace srook

#endif
#endif
