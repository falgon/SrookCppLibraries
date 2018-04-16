// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_IO2D_THIRD_PARTY_OPENGL_GLUT_DETAIL_GLOBALP_HPP
#define INCLUDED_SROOK_IO2D_THIRD_PARTY_OPENGL_GLUT_DETAIL_GLOBALP_HPP

#include <srook/io2d/third_party/opengl/glut/detail/config.hpp>
#include <srook/io2d/third_party/opengl/glut/detail/globalp.h>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <atomic>
#include <vector>
#include <srook/math/geometry/fundamental/point.hpp>
#include <srook/io2d/third_party/opengl/glut/utility/params.hpp>
#include <srook/type_traits/is_equality_comparable.hpp>

SROOK_NESTED_NAMESPACE(srook, io2d, glut) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class Algo>
struct globalp {
    typedef srook::math::geometry::fundamental::point<SROOK_DEDUCED_TYPENAME Algo::point_type::value_type> point_type;
    typedef std::vector<SROOK_DEDUCED_TYPENAME Algo::argument_type> dots_type;

    SROOK_FORCE_INLINE globalp(utility::params p, std::size_t g = 1024)
        : p_(p), granularity_(g), dots_() {}

    SROOK_FORCE_INLINE SROOK_CONSTEXPR std::pair<utility::params::wsize_type, utility::params::wsize_type> 
    winsize() const SROOK_NOEXCEPT(is_nothrow_equality_comparable<utility::params::wsize_type>::value)
    {
        typedef utility::params::wsize_type wsize_type;
        return { value_or(p_.w_, wsize_type(0), wsize_type(640)), value_or(p_.h_, wsize_type(0), wsize_type(480)) }; 
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR std::pair<int, char**> 
    args() const SROOK_NOEXCEPT_TRUE 
    { 
        return { p_.argc_, p_.argv_ };
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME utility::params::title_type::const_pointer
    title() const SROOK_NOEXCEPT_TRUE
    {
        return p_.title_.empty() ? "Srook C++ Libraries: glut painter" : p_.title_.data();
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR std::pair<utility::params::position_type, utility::params::position_type>
    position() const SROOK_NOEXCEPT_TRUE
    {
        return { p_.wpos_, p_.hpos_ };
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR std::size_t granularity() const SROOK_NOEXCEPT_TRUE
    {
        return granularity_;
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR dots_type& dots() SROOK_NOEXCEPT_TRUE { return dots_; }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_FORCE_INLINE SROOK_CONSTEXPR const dots_type& dots() const SROOK_NOEXCEPT_TRUE { return dots_; }
#endif

#if SROOK_CPP_INLINE_VARIABLES && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
    SROOK_INLINE_VARIABLE static std::atomic<globalp<Algo>*> gpp = SROOK_NULLPTR;
#else
    static std::atomic<globalp<Algo>*> gpp;
#endif
private:
    template <class U>
    SROOK_CONSTEXPR SROOK_FORCE_INLINE U& value_or(U u, U c, U val) const
    SROOK_NOEXCEPT(is_nothrow_equality_comparable<U>::value)
    {
        return u != c ? u : val;
    }

    utility::params p_;
    dots_type dots_;
    std::size_t granularity_;
};

#if !(SROOK_CPP_INLINE_VARIABLES && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT)
template <class T>
std::atomic<globalp<T>*> globalp<T>::gpp = SROOK_NULLPTR;
#endif

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(glut, io2d, srook)

#endif
#endif
