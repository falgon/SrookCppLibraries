// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_ALGORITHM_CODING_ZLIB_EXCEPTION_HPP
#define INCLUDED_SROOK_ALGORITHM_CODING_ZLIB_EXCEPTION_HPP

#include <srook/algorithm/coding/zlib/config.hpp>
#include <exception>
#include <string>
#include <srook/string/to_string.hpp>

namespace srook {
namespace algorithm {
namespace zlib {
SROOK_INLINE_NAMESPACE(v1)

class zlib_exception : public std::exception {
public:
    zlib_exception(z_stream* zptr, int ret) : msg_("srook::algorithm::zlib: ")
    {
        switch (ret) {
            case Z_STREAM_ERROR:
                msg_ += "Z_STREAM_ERROR: ";  break;
            case Z_DATA_ERROR:
                msg_ += "Z_DATA_ERROR: ";    break;
            case Z_MEM_ERROR:
                msg_ += "Z_MEM_ERROR: ";     break;
            case Z_VERSION_ERROR:
                msg_ += "Z_VERSION_ERROR: The library version is "; 
                msg_ += std::string(zlibVersion()); 
                msg_ += ": ";
                break;
            case Z_BUF_ERROR:
                msg_ += "Z_BUF_ERROR: ";     break;
            default:
                msg_ += "[" + to_string(srook::move(ret)) + "]: ";
        }
        msg_ += zptr->msg ? zptr->msg : "";
    }
    zlib_exception(const std::string& str) : msg_(str) {}
    const char* what() const SROOK_NOEXCEPT_TRUE SROOK_OVERRIDE { return msg_.c_str(); }
private:
    std::string msg_;
};


SROOK_INLINE_NAMESPACE_END
} // namespace zlib
} // namespace algorithm
} // namespace srook

#endif
