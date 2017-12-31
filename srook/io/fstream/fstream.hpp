// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_IO_FSTREAM_FSTREAM_HPP
#define INCLUDED_SROOK_IO_FSTREAM_FSTREAM_HPP

#include <srook/io/fstream/config.hpp>

namespace srook {
namespace io {
SROOK_INLINE_NAMESPACE(v1) 

class fstream : public std::fstream {
public:
    typedef std::fstream base_type;
    fstream() SROOK_DEFAULT
    fstream(const std::string& filename, std::ios_base::openmode mode = std::ios_base::in)
    {
        open(filename, mode);
    }
    void open(const std::string& filename, std::ios_base::openmode mode = std::ios_base::in)
    {
        mode |= std::ios_base::in;
        exceptions(std::ios_base::badbit);
        detail::check_mode(filename, mode);
        base_type::open(filename, mode);
        detail::check_open(this, filename, mode);
        detail::check_peek(this, filename, mode);
    }
};

SROOK_INLINE_NAMESPACE_END
} // namespace io
} // namespace srook

#endif
