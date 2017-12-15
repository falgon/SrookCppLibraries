// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_ALGORITHM_CODING_ZLIB_OFSTREAM_HPP
#define INCLUDED_SROOK_ALGORITHM_CODING_ZLIB_OFSTREAM_HPP

#include <srook/algorithm/coding/zlib/ifstream.hpp>
#include <srook/io/fstream/ofstream.hpp>
#include <string>
#include <fstream>

namespace srook {
namespace algorithm {
namespace zlib {
SROOK_INLINE_NAMESPACE(v1)
    
class ofstream 
    : private detail::fstream_holder<srook::io::ofstream>, public std::ostream {
public:
    typedef detail::fstream_holder<srook::io::ofstream> base_type1;
    typedef std::ostream base_type2;
    explicit ofstream(const std::string& filename, std::ios_base::openmode mode = std::ios_base::out)
        : base_type1(filename, mode | std::ios_base::binary), base_type2(new ostreambuf(fs_.rdbuf(), compress_level::level6))
    {
        exceptions(std::ios_base::badbit);
    }
    
    explicit ofstream(const std::string& filename, compress_level lv = compress_level::level6, std::ios_base::openmode mode = std::ios_base::out)
        : base_type1(filename, mode | std::ios_base::binary), base_type2(new ostreambuf(fs_.rdbuf(), srook::move(lv)))
    {
        exceptions(std::ios_base::badbit);
    }

    virtual ~ofstream() SROOK_OVERRIDE
    {
        if (rdbuf()) delete rdbuf();
    }
};

SROOK_INLINE_NAMESPACE_END
} // namespace zlib
} // namespace algorithm
} // namespace srook

#endif
