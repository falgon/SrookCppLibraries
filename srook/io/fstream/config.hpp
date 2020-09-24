// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_IO_FSTREAM_CONFIG_HPP
#define INCLUDED_SROOK_IO_FSTREAM_CONFIG_HPP
#include <srook/io/fstream/exception.hpp>
#include <srook/array.hpp>
#include <srook/string/strerror.hpp>
#include <fstream>
#include <string>

namespace srook {
namespace io {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

std::string openmode_to_string(std::ios_base::openmode mode)
{
    using std::ios_base;

    SROOK_CONSTEXPR_OR_CONST std::size_t mode_type = 6;
    SROOK_CONSTEXPR_OR_CONST array<std::ios_base::openmode, mode_type> mode_val = 
        { ios_base::in, ios_base::out, ios_base::app, ios_base::ate, ios_base::trunc, ios_base::binary };
    SROOK_CONSTEXPR_OR_CONST array<const char*, mode_type> mode_name =
        { "in", "out", "app", "ate", "trunc", "binary" };

    std::string r;
    {
        std::size_t i = 0;
        for(auto&& mv : mode_val) {
            if (mode & mv) {
                r += (!r.empty() ? "|" : "");
                r += mode_name[i];
            }
            ++i;
        }
    }
    if (r.empty()) r = "none";
    return r;
}

void check_mode(const std::string& filename, std::ios_base::openmode mode)
{
    using namespace srook::io::exception;

    if ((mode & std::ios_base::trunc) && !(mode & std::ios_base::out)) {
        SROOK_THROW fstream_exception(std::string("srook::io::fstream: open('") + filename + "'): mode error: trunc and not out");
    } else if ((mode & std::ios_base::app) & !(mode & std::ios_base::out)) {
        SROOK_THROW fstream_exception(std::string("srook::io::fstream: open('") + filename + "'): mode error: app and not out");
    } else if ((mode & std::ios_base::trunc) && (mode & std::ios_base::app)) {
        SROOK_THROW fstream_exception(std::string("srook::io::fstream: open('") + filename + "'): mode error: trunc and app");
    }
}

void check_open(std::ios* iosptr, const std::string& filename, std::ios_base::openmode mode)
{
    if (iosptr->fail()) {
        SROOK_THROW srook::io::exception::fstream_exception(std::string("srook::io::fstream: open('") + filename + "'," + openmode_to_string(mode) + "): open failed: " + srook::string::strerror());
    }
}

void check_peek(std::istream* isptr, const std::string& filename, std::ios_base::openmode mode)
{
    bool peek_failed = true;
    try {
        isptr->peek();
        peek_failed = isptr->fail();
    } catch (std::ios_base::failure) {}

    if (peek_failed) {
        SROOK_THROW srook::io::exception::fstream_exception(std::string("srook::io::fstream: open('") + filename + "'," + openmode_to_string(mode) + "): peek failed: " + srook::string::strerror());
    }

    isptr->clear();
}

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} // namespace io
} // namespace srook

#endif
