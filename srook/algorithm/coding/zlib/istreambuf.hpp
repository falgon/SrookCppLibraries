// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_ALGORITHM_CODIG_ZLIB_ISTREAMBUF_HPP
#define INCLUDED_SROOK_ALGORITHM_CODIG_ZLIB_ISTREAMBUF_HPP

#include <cassert>
#include <srook/algorithm/coding/zlib/z_streamer.hpp>
#include <srook/algorithm/coding/zlib/exception.hpp>
#include <srook/memory/unique_ptr.hpp>
#include <srook/cstddef/byte.hpp>
#include <type_traits>
#include <streambuf>

namespace srook {
namespace algorithm {
namespace zlib {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

namespace {
#ifdef POSSIBLE_TO_INCLUDE_STD_MEMORY
using std::make_unique;
#elif defined(POSSIBLE_TO_INCLUDE_BOOST_UNIQUE_PTR)
using boost::make_unique;
#else
using srook::make_unique;
#endif
} // namespace anonymouse

} // namespace detail

class istreambuf 
    : public std::streambuf, private noncopyable<istreambuf> {
public:
    typedef std::streambuf base_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::char_type char_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::int_type int_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::traits_type traits_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::pos_type pos_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::off_type off_type;

    istreambuf(std::streambuf* sbuf_ptr, std::size_t buffer_size = default_buffer_size, bool ad = true)
        : sbuf_ptr_(sbuf_ptr), 
          in_buff(detail::make_unique<char_type[]>(buffer_size)),
          zptr_(SROOK_NULLPTR),
          out_buff(detail::make_unique<char_type[]>(buffer_size)),
          in_buff_begin(in_buff.get()),
          in_buff_end(in_buff.get()),
          buff_size(buffer_size), 
          auto_detect(ad), 
          auto_detect_run(false), 
          is_text(false)
    {
        assert(sbuf_ptr_);
        setg(out_buff.get(), out_buff.get(), out_buff.get());
    }

    virtual ~istreambuf() SROOK_OVERRIDE SROOK_DEFAULT

    virtual int_type underflow() SROOK_OVERRIDE
    {
        if (gptr() == egptr()) {
            char_type* out_buff_t = out_buff.get();
            do {
                if (in_buff_begin == in_buff_end) {
                    in_buff_begin = in_buff.get();
                    std::streamsize sz = sbuf_ptr_->sgetn(reinterpret_cast<char*>(in_buff.get()), buff_size);
                    in_buff_end = in_buff.get() + sz;
                    if (in_buff_end == in_buff_begin) break;
                }

                if (auto_detect && !auto_detect_run) {
                    auto_detect_run = true;
                    typedef SROOK_DEDUCED_TYPENAME std::make_unsigned<char_type>::type uchar_type;
                    uchar_type b0 = *in_buff_begin;
                    uchar_type b1 = *(in_buff_begin + 1);
                    
                    // reference: 
                    //  * https://tools.ietf.org/html/rfc1950
                    //  * https://stackoverflow.com/questions/9050260/what-does-a-zlib-header-look-like/30794147#30794147
                    is_text = !(in_buff_begin + 2 <= in_buff_end && ((b0 == 0x1f && b1 == 0x8b) || (b0 == 0x78 && (b1 == 0x01 || b1 == 0x9c || b1 == 0xda))));
                }

                if (is_text) {
                    assert(in_buff_begin == in_buff.get());
                    in_buff.swap(out_buff);
                    out_buff_t = in_buff_end;
                    in_buff_begin = in_buff.get();
                    in_buff_end = in_buff.get();
                } else {
                    if (!zptr_) zptr_.reset(new srook::algorithm::zlib::z_streamer(stream_mode::input, compress_level::level6));
                    zptr_->next_in = reinterpret_cast<Bytef*>(in_buff_begin);
                    zptr_->avail_in = static_cast<uInt>(in_buff_end - in_buff_begin);
                    zptr_->next_out = reinterpret_cast<Bytef*>(out_buff_t);
                    zptr_->avail_out = static_cast<uInt>((out_buff.get() + buff_size) - out_buff_t);
                    const int ret = inflate(zptr_.get(), Z_NO_FLUSH);

                    if (ret != Z_OK && ret != Z_STREAM_END) SROOK_THROW zlib_exception(zptr_.get(), ret);
                    in_buff_begin = reinterpret_cast<char*>(zptr_->next_in);
                    in_buff_end = in_buff_begin + zptr_->avail_in;
                    out_buff_t = reinterpret_cast<char*>(zptr_->next_out);
                    assert(out_buff_t + zptr_->avail_out == out_buff.get() + buff_size);

                    if (ret == Z_STREAM_END) {
                        zptr_.reset();
                    }
                }
            } while (out_buff_t == out_buff.get());
            setg(out_buff.get(), out_buff.get(), out_buff_t);
        }

        return gptr() == egptr() ? traits_type::eof() : traits_type::to_int_type(*gptr());
    }
private:
    std::streambuf* sbuf_ptr_;

#ifdef POSSIBLE_TO_INCLUDE_STD_MEMORY
    std::unique_ptr<char_type[]>
#elif defined(POSSIBLE_TO_INCLUDE_BOOST_UNIQUE_PTR)
    boost::unique_ptr<char_type[]>
#else
    unique_ptr<char_type[]>
#endif
    in_buff;

#ifdef POSSIBLE_TO_INCLUDE_STD_MEMORY
    std::unique_ptr<srook::algorithm::zlib::z_streamer>
#elif defined(POSSIBLE_TO_INCLUDE_BOOST_UNIQUE_PTR)
    boost::unique_ptr<srook::algorithm::zlib::z_streamer>
#else
    unique_ptr<srook::algorithm::zlib::z_streamer>
#endif
    zptr_;

#ifdef POSSIBLE_TO_INCLUDE_STD_MEMORY
    std::unique_ptr<char_type[]>
#elif defined(POSSIBLE_TO_INCLUDE_BOOST_UNIQUE_PTR)
    boost::unique_ptr<char_type[]>
#else
    unique_ptr<char_type[]>
#endif
    out_buff;
    
    char_type* in_buff_begin;
    char_type* in_buff_end;
    std::size_t buff_size;
    bool auto_detect;
    bool auto_detect_run;
    bool is_text;
    static SROOK_CONSTEXPR_OR_CONST std::size_t default_buffer_size = static_cast<std::size_t>(1) << 20;
};


SROOK_INLINE_NAMESPACE_END
} // namespace zlib
} // namespace algorithm
} // namespace srook

#endif
