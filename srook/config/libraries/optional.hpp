#ifndef INCLUDED_SROOK_CONFIG_LIBRARIES_OPTIONAL_HPP
#define INCLUDED_SROOK_CONFIG_LIBRARIES_OPTIONAL_HPP

#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>

#if SROOK_HAS_INCLUDE(<optional>) && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
#	include <optional>
#	define OPTIONAL std::optional
#	define NULLOPT_T std::nullopt_t
#	define NULLOPT std::nullopt
#else
#	include <srook/optional.hpp>
#	define OPTIONAL srook::optionally::optional
#	define NULLOPT_T srook::optionally::nullopt_t
#	define NULLOPT srook::optionally::nullopt
#endif

#define SROOK_OPTIONAL OPTIONAL
#define SROOK_NULLOPT_T NULLOPT_T
#define SROOK_NULLOPT NULLOPT
namespace srook {
namespace libraries {
SROOK_INLINE_NAMESPACE(v1)

using OPTIONAL;
using NULLOPT_T;
using NULLOPT;

SROOK_INLINE_NAMESPACE_END
} // libraries
} // srook

#endif
