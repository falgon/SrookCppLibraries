// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_ALGORITHM_CODING_ZLIB_OSTREAM_HPP
#define INCLUDED_SROOK_ALGORITHM_CODING_ZLIB_OSTREAM_HPP
#include <srook/algorithm/coding/zlib/config.hpp>
#include <srook/algorithm/coding/zlib/ostreambuf.hpp>
#include <srook/memory.hpp>
#include <ostream>

namespace srook {
namespace algorithm {
namespace zlib {
SROOK_INLINE_NAMESPACE(v1)

class ostream : public std::ostream {
public:
    typedef std::ostream base_type;
    ostream(std::ostream& os, compress_level lv = compress_level::level6) 
        : base_type(srook::addressof(osbuf)), osbuf(os.rdbuf(), srook::move(lv))
    {
        exceptions(std::ios_base::badbit);
    }
    explicit ostream(std::streambuf* sbufptr, compress_level lv = compress_level::level6) 
        : base_type(srook::addressof(osbuf)), osbuf(sbufptr, srook::move(lv))
    {
        exceptions(std::ios_base::badbit);
    }
private:
    ostreambuf osbuf;
};

SROOK_INLINE_NAMESPACE_END
} // namespace zlib
} // namespace algorithm
} // namespace srook

#endif
