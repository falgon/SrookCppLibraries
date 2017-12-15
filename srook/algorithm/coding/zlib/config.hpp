// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_ALGORITHM_CODING_ZLIB_CONFIG_HPP
#define INCLUDED_SROOK_ALGORITHM_CODING_ZLIB_CONFIG_HPP

#include <srook/config.hpp>
#include <srook/utility.hpp>
#include <zlib.h>

namespace srook {
namespace algorithm {
namespace zlib {
SROOK_INLINE_NAMESPACE(v1)

struct SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT read_file_t {
    explicit read_file_t() SROOK_DEFAULT
};
struct SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT read_string_t {
    explicit read_string_t() SROOK_DEFAULT
};
    
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR read_file_t read_file {};
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR read_string_t read_string {};
#else
extern const read_file_t read_file;
extern const read_string_t read_string;
#endif

SROOK_STRONG_ENUM_BEGIN(compress_level) {
    none = Z_NO_COMPRESSION, 
    level1 = 1, 
    level2 = 2, 
    level3 = 3, 
    level4 = 4,
    level5 = 5, 
    level6 = Z_DEFAULT_COMPRESSION,
    level7 = 7, 
    level8 = 8, 
    level9 = Z_BEST_COMPRESSION,
    best = level9
};
SROOK_STRONG_ENUM_EPILOG(compress_level)

typedef uInt uint;

SROOK_INLINE_NAMESPACE_END
} // namespace zlib
} // namespace algorithm
} // namespace srook

#endif
