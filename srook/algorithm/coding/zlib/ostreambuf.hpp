// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_CODIG_ZLIB_OSTREAMBUF_HPP
#define INCLUDED_SROOK_ALGORITHM_CODIG_ZLIB_OSTREAMBUF_HPP

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

class ostreambuf 
    : public std::streambuf,
    private noncopyable<ostreambuf> {
public:
    typedef std::streambuf base_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::char_type char_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::int_type int_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::traits_type traits_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::pos_type pos_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::off_type off_type;

    ostreambuf(std::streambuf* sbuf_ptr, uint buffer_size = default_buffer_size, compress_level lv = compress_level::level6)
        : sbuf_ptr_(sbuf_ptr), 
          in_buff(detail::make_unique<char_type[]>(buffer_size)),
          zptr_(detail::make_unique<srook::algorithm::zlib::z_streamer>(stream_mode::output, lv)),
          out_buff(detail::make_unique<char_type[]>(buffer_size)),
          buff_size(buffer_size)
    {
        assert(sbuf_ptr_);
        setp(in_buff.get(), in_buff.get() + buff_size);
    }
    
    ostreambuf(std::streambuf* sbuf_ptr, compress_level lv = compress_level::level6)
        : sbuf_ptr_(sbuf_ptr), 
          in_buff(detail::make_unique<char_type[]>(default_buffer_size)),
          zptr_(detail::make_unique<srook::algorithm::zlib::z_streamer>(stream_mode::output, lv)),
          out_buff(detail::make_unique<char_type[]>(default_buffer_size)),
          buff_size(default_buffer_size)
    {
        assert(sbuf_ptr_);
        setp(in_buff.get(), in_buff.get() + buff_size);
    }

    virtual ~ostreambuf() SROOK_OVERRIDE
    {
        sync();
    }

    int apply_deflate(int flush)
    {
        while (true) {
            zptr_->next_out = reinterpret_cast<Bytef*>(out_buff.get());
            zptr_->avail_out = buff_size;
            const int ret = deflate(zptr_.get(), flush);
            if (ret != Z_OK && ret != Z_STREAM_END && ret != Z_BUF_ERROR) SROOK_THROW zlib_exception(zptr_.get(), ret);
            std::streamsize sz = sbuf_ptr_->sputn(out_buff.get(), zptr_->next_out - reinterpret_cast<Bytef*>(out_buff.get()));
            if (sz != zptr_->next_out - reinterpret_cast<Bytef*>(out_buff.get())) {
                return -1;
            }
            if (ret == Z_STREAM_END || ret == Z_BUF_ERROR || sz == 0) {
                break;
            }
        }
        return 0;
    }

    virtual int_type overflow(int_type c = traits_type::eof()) SROOK_OVERRIDE
    {
        zptr_->next_in = reinterpret_cast<Bytef*>(pbase());
        zptr_->avail_in = uint(pptr() - pbase());
        while (zptr_->avail_in > 0) {
            int r = apply_deflate(Z_NO_FLUSH);
            if (r != 0) {
                setp(SROOK_NULLPTR, SROOK_NULLPTR);
                return traits_type::eof();
            }
        }
        setp(in_buff.get(), in_buff.get() + buff_size);
        return traits_type::eq_int_type(c, traits_type::eof()) ? traits_type::eof() : sputc(char_type(c));
    }

    virtual int sync() SROOK_OVERRIDE
    {
        overflow();
        if (!pptr()) return -1;

        zptr_->next_in = SROOK_NULLPTR;
        zptr_->avail_in = 0;
        if (apply_deflate(Z_FINISH) != 0) return -1;
        deflateReset(zptr_.get());
        return 0;
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
    
    uint buff_size = 0;
    static SROOK_CONSTEXPR_OR_CONST std::size_t default_buffer_size = static_cast<std::size_t>(1) << 20;
};


SROOK_INLINE_NAMESPACE_END
} // namespace zlib
} // namespace algorithm
} // namespace srook

#endif
