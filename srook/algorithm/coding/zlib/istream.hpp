// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_ALGORITHM_CODING_ZLIB_ISTREAM_HPP
#define INCLUDED_SROOK_ALGORITHM_CODING_ZLIB_ISTREAM_HPP

#include <srook/algorithm/coding/zlib/config.hpp>
#include <srook/algorithm/coding/zlib/istreambuf.hpp>
#include <srook/memory.hpp>
#include <istream>

namespace srook {
namespace algorithm {
namespace zlib {
SROOK_INLINE_NAMESPACE(v1)

class istream : public std::istream {
public:
    typedef std::istream base_type;
    istream(std::istream& is) : base_type(srook::addressof(isbuf)), isbuf(is.rdbuf())
    {
        exceptions(std::ios_base::badbit);
    }
    explicit istream(std::streambuf* sbufptr) : base_type(srook::addressof(isbuf)), isbuf(sbufptr)
    {
        exceptions(std::ios_base::badbit);
    }
private:
    istreambuf isbuf;
};

SROOK_INLINE_NAMESPACE_END
} // namespace zlib
} // namespace algorithm
} // namespace srook

#endif
