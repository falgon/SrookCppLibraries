// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_CODING_ZLIB_IFSTREAM_HPP
#define INCLUDED_SROOK_ALGORITHM_CODING_ZLIB_IFSTREAM_HPP

#include <srook/algorithm/coding/zlib/istreambuf.hpp>
#include <srook/io/fstream/ifstream.hpp>
#include <srook/memory/utility/checked_delete.hpp>
#include <string>
#include <fstream>

namespace srook {
namespace algorithm {
namespace zlib {
SROOK_INLINE_NAMESPACE(v1)
    
namespace detail {

template <class FileStream>
struct fstream_holder {
    fstream_holder(const std::string& filename, std::ios_base::openmode mode)
        : fs_(filename, mode) {}
    FileStream fs_;
};

} // namespace detail

class ifstream 
    : private detail::fstream_holder<srook::io::ifstream>, public std::istream {
public:
    typedef detail::fstream_holder<srook::io::ifstream> base_type1;
    typedef std::istream base_type2;
    explicit ifstream(const std::string& filename, std::ios_base::openmode mode = std::ios_base::in)
        : base_type1(filename, mode), base_type2(new istreambuf(fs_.rdbuf()))
    {
        exceptions(std::ios_base::badbit);
    }

    virtual ~ifstream() SROOK_OVERRIDE
    {
        checked_delete(rdbuf());
    }
};

SROOK_INLINE_NAMESPACE_END
} // namespace zlib
} // namespace algorithm
} // namespace srook

#endif
