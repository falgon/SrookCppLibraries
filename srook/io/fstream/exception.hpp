// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_IO_FSTREAM_EXCEPTION
#define INCLUDED_SROOK_IO_FSTREAM_EXCEPTION

#include <srook/config.hpp>
#include <exception>
#include <string>

namespace srook {
namespace io {
namespace exception {
SROOK_INLINE_NAMESPACE(v1)

class fstream_exception : public std::exception {
public:
    typedef std::exception base_type;
    fstream_exception(const std::string& m) : msg_(m) {}
    const char* what() const SROOK_NOEXCEPT_TRUE SROOK_OVERRIDE { return msg_.c_str(); }
private:
    std::string msg_;
};

SROOK_INLINE_NAMESPACE_END
} // namespace exception
} // namespace io
} // namespace srook

#endif
