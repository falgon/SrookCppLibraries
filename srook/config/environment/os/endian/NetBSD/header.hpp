#ifndef INCLUDED_SROOK_CONFIG_ENV_OS_NETBSD_HEADER_HPP
#define INCLUDED_SROOK_CONFIG_ENV_OS_NETBSD_HEADER_HPP

#ifdef __NetBSD__
#	include <sys/endian.h>
#	if _BYTE_ORDER == _LITTLE_ENDIAN
#		define SROOK_LITTLE_ENDIAN 1
#		define SROOK_BIG_ENDIAN 0
#	else
#		define SROOK_LITTLE_ENDIAN 0
#		define SROOK_BIG_ENDIAN 1
#	endif
#	define SROOK_HAS_QUICK_EXIT
#endif

#endif
