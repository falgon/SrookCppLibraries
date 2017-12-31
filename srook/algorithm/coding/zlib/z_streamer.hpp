// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_CODING_ZLIB_Z_STREAM_HPP
#define INCLUDED_SROOK_ALGORITHM_CODING_ZLIB_Z_STREAM_HPP

#include <srook/algorithm/coding/zlib/config.hpp>
#include <srook/algorithm/coding/zlib/exception.hpp>

namespace srook {
namespace algorithm {
namespace zlib {
SROOK_INLINE_NAMESPACE(v1)

SROOK_STRONG_ENUM_BEGIN(stream_mode) {
    input, output
};
SROOK_STRONG_ENUM_EPILOG(stream_mode)

class z_streamer : public ::z_stream {
public:
    z_streamer(stream_mode sm = stream_mode::input, compress_level lv = compress_level::level6) SROOK_NOEXCEPT(false)
        : s(sm)
    {
        this->zalloc = Z_NULL;
        this->zfree = Z_NULL;
        this->opaque = Z_NULL;

        int ret;
        switch (s) {
            case stream_mode::input: {
                this->avail_in = 0;
                this->next_in = Z_NULL;
            
                // Quote from zlib 1.2.11 Manual
                //
                // windowBits can also be greater than 15 for optional gzip decoding. 
                // Add 32 to windowBits to enable zlib and gzip decoding with automatic header detection, 
                // or add 16 to decode only the gzip format (the zlib format will return a Z_DATA_ERROR).
                SROOK_CONSTEXPR_OR_CONST int windowBits = 15 + 32;
                ret = inflateInit2(this, windowBits);
                break;
            }
            case stream_mode::output: {
                // Quote from zlib 1.2.11 Manual
                //
                // windowBits can also be greater than 15 for optional gzip encoding. 
                // Add 16 to windowBits to write a simple gzip header and trailer around the compressed data instead of a zlib wrapper.
                SROOK_CONSTEXPR_OR_CONST int windowBits = 15 + 16;

                // Quote from zlib 1.2.11 Manual
                //
                // The memLevel parameter specifies how much memory should be allocated for the internal compression state. 
                // memLevel=1 uses minimum memory but is slow and reduces compression ratio; 
                // memLevel=9 uses maximum memory for optimal speed. 
                // The default value is 8.
                SROOK_CONSTEXPR_OR_CONST int memLevel = 8;
                ret = deflateInit2(this, static_cast<int>(lv), Z_DEFLATED, windowBits, memLevel, Z_DEFAULT_STRATEGY);
                break;
            }
            default:
                ret = Z_VERSION_ERROR;
        }
        if (ret != Z_OK) SROOK_THROW zlib_exception(this, ret);
    }
    
    ~z_streamer()
    {
        if (s == stream_mode::input) inflateEnd(this);
        else if (s == stream_mode::output) deflateEnd(this);
    }
private:
    stream_mode s;
};

SROOK_INLINE_NAMESPACE_END
} // namespace zlib
} // namespace algorithm
} // namespace srook

#endif
