#ifndef INCLUDED_SROOK_CONFIG_OPTIONAL_HPP
#define INCLUDED_SROOK_CONFIG_OPTIONAL_HPP

/*#if __has_include(<optional>)
#	include<optional>
#	define OPTIONAL std::optional
#	define NULLOPT_T std::nullopt_t
#	define NULLOPT std::nullopt
#elif __has_include(<boost/optional.hpp>)
#	include<boost/optional.hpp>
#	define OPTIONAL boost::optional
#	define NULLOPT_T boost::none_t
#	define NULLOPT boost::none
#else*/
#	include<srook/optional.hpp>
#	define OPTIONAL srook::optional
#	define NULLOPT_T srook::nullopt_t
#	define NULLOPT srook::nullopt
//#endif

#endif
