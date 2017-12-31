// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_IO_FSTREAM_OFSTREAM_HPP
#define INCLUDED_SROOK_IO_FSTREAM_OFSTREAM_HPP

#include <srook/io/fstream/config.hpp>

namespace srook {
namespace io {
SROOK_INLINE_NAMESPACE(v1) 

class ofstream : public std::ofstream {
public:
    typedef std::ofstream base_type;
    ofstream() SROOK_DEFAULT
    ofstream(const std::string& filename, std::ios_base::openmode mode = std::ios_base::out)
    {
        open(filename, mode);
    }
    void open(const std::string& filename, std::ios_base::openmode mode = std::ios_base::out)
    {
        mode |= std::ios_base::out;
        exceptions(std::ios_base::badbit);
        detail::check_mode(filename, mode);
        base_type::open(filename, mode);
        detail::check_open(this, filename, mode);
    }
};

SROOK_INLINE_NAMESPACE_END
} // namespace io
} // namespace srook

#endif
