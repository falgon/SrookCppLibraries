// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_IO2D_THIRD_PARTY_OPENGL_GLUT_UTILITY_PARAMS_HPP
#define INCLUDED_SROOK_IO2D_THIRD_PARTY_OPENGL_GLUT_UTILITY_PARAMS_HPP

#include <srook/io2d/third_party/opengl/glut/detail/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/io2d/third_party/opengl/glut/detail/globalp.h>
#include <srook/math/geometry/fundamental/point.hpp>
#include <srook/string/string_view.hpp>
#include <srook/optional.hpp>

#ifdef __GNUC__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wpadded"
#endif
#ifdef __clang__
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wpadded"
#endif

SROOK_NESTED_NAMESPACE(srook, io2d, glut, utility) {
SROOK_INLINE_NAMESPACE(v1)

struct params {
    SROOK_CONSTEXPR SROOK_FORCE_INLINE params(int argc, char** argv) SROOK_NOEXCEPT_TRUE
        : w_(0), h_(0), argc_(srook::move(argc)), argv_(argv), title_(), wpos_(0), hpos_(0) {}

    SROOK_FORCE_INLINE params& 
    operator()(GLfloat w, GLfloat h, srook::optional<std::size_t> wpos = srook::nullopt, srook::optional<std::size_t> hpos = srook::nullopt) SROOK_NOEXCEPT_TRUE
    {
        w_ = srook::move(w);
        h_ = srook::move(h);
        wpos >>= [this](std::size_t x) -> srook::optional<std::size_t> { return { wpos_ = x }; };
        hpos >>= [this](std::size_t x) -> srook::optional<std::size_t> { return { hpos_ = x }; };
        return *this;
    }

    SROOK_FORCE_INLINE params&
    operator()(srook::string_view t) SROOK_NOEXCEPT_TRUE
    {
        title_ = srook::move(t);
        return *this;
    }
private:
    template <class>
    friend struct srook::io2d::glut::detail::globalp;

    typedef GLfloat wsize_type;
    typedef srook::string_view title_type;
    typedef std::size_t position_type;

    wsize_type w_, h_;
    int argc_;
    char** argv_;
    title_type title_;
    std::size_t wpos_, hpos_;
};


SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(utility, glut, io2d, srook)

#ifdef __GNUC__
#   pragma GCC diagnostic pop
#endif
#ifdef __clang__
#   pragma clang diagnostic pop
#endif

#endif
#endif
