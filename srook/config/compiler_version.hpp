#ifndef INCLUDED_SROOK_CONFIG_COMPILER_VERSION_HPP
#define INCLUDED_SROOK_CONFIG_COMPILER_VERSION_HPP

#if !defined(__APPLE__) &&\
   	!defined(__clang_major__) &&\
	!defined(__clang_minor__) &&\
	!defined(__clang_patchlevel__) &&\
	defined(__GNUC__) &&\
	defined(__GNUC_MINOR__) &&\
	defined(__GNUC_PATCHLEVEL__)
#define SROOK_GCC_VERSION __GNUC__*100 + __GNUC_MINOR__*10 + __GNUC_PATCHLEVEL__

#elif !defined(__APPLE__) &&\
	defined(__clang_major__) &&\
	defined(__clang_minor__) &&\
	defined(__clang_patchlevel__)
#define SROOK_CLANG_VERSION __clang_major__*100 + __clang_minor__*10 + __clang_patchlevel__

#elif defined(__APPLE__)
#if defined(__clang_major__) && defined(___clang_minor__) && defined(__clang_patchlevel__)
#define SROOK_APPLE_CLANG_VERSION __clang_major__*100 + __clang_minor__*10 + __clang_patchlevel__
#elif defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__GNUC_PATCHLEVEL__)
#define SROOK_APPLE_GCC_VERSION __GNUC__*100 + __GNUC_MINOR__*10 + __GNUC_PATCHLEVEL__
#endif

#endif
#endif
