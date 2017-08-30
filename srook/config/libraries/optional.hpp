#ifndef INCLUDED_SROOK_CONFIG_LIBRARIES_OPTIONAL_HPP
#define INCLUDED_SROOK_CONFIG_LIBRARIES_OPTIONAL_HPP

#include<srook/config/cpp_predefined/feature_testing.hpp>

#if SROOK_HAS_INCLUDE(<optional>)
#	include<optional>
#	define OPTIONAL std::optional
#	define NULLOPT_T std::nullopt_t
#	define NULLOPT std::nullopt
#elif SROOK_HAS_INCLUDE(<boost/optional.hpp>)
#	include<boost/optional.hpp>
#	define OPTIONAL boost::optional
#	define NULLOPT_T boost::none_t
#	define NULLOPT boost::none
#else
#	include<srook/optional.hpp>
#	define OPTIONAL srook::optional
#	define NULLOPT_T srook::nullopt_t
#	define NULLOPT srook::nullopt
#endif

#define SROOK_OPTIONAL OPTIONAL
#define SROOK_NULLOPT_T NULLOPT_T
#define SROOK_NULLOPT NULLOPT

#endif
