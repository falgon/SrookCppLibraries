#ifndef INCLUDED_SROOK_UTILITY_LIBRARIES_BYTE_HPP
#define INCLUDED_SROOK_UTILITY_LIBRARIES_BYTE_HPP

#include<srook/config/compiler.hpp>

#ifdef SROOK_IS_CXX17
#include<cstddef>
#define SROOK_BYTE std::byte
#define SROOK_BYTE_TO_INTEGER std::to_integer
#else
#include<srook/cstddef/byte.hpp>
#define SROOK_BYTE srook::byte
#define SROOK_BYTE_TO_INTEGER srook::to_integer
#endif

#endif
