// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_IO2D_THIRD_PARTY_OPENCV_GLUT_UTILITY_LINE_HPP
#define INCLUDED_SROOK_IO2D_THIRD_PARTY_OPENCV_GLUT_UTILITY_LINE_HPP

#include <srook/io2d/third_party/opengl/glut/detail/config.hpp>
#include <srook/math/geometry/algorithm/line/straight/points.hpp>
#include <srook/type_traits/decay.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <atomic>
#include <srook/mutex/mutexes/mutex.hpp>
#include <srook/mutex/guards/lock_guard.hpp>
#include <srook/memory/addressof.hpp>

#ifdef __GNUC__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#ifdef __clang__
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

SROOK_NESTED_NAMESPACE(srook, io2d, glut, utility) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T = double>
struct st_arguments {
    typedef std::vector<std::pair<srook::math::geometry::fundamental::point<T>, srook::math::geometry::fundamental::point<T>>> dots_type;
    st_arguments(GLfloat w, GLfloat h) : w_(srook::move(w)), h_(srook::move(h)), dots() {}

    GLfloat w_, h_;
    dots_type dots;
};

std::atomic<st_arguments<>*> arguments = SROOK_NULLPTR;

} // namespace detail

class gsline {
public:
    typedef double value_type;
    typedef std::pair<srook::math::geometry::fundamental::point<value_type>, srook::math::geometry::fundamental::point<value_type>> argument_type;
    SROOK_FORCE_INLINE gsline(int argc, char** argv, const char* title, GLfloat w, GLfloat h, std::size_t wpos = 100, std::size_t hpos = 100)
        : title_(title)
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(static_cast<int>(wpos), static_cast<int>(hpos));
        glutInitWindowSize(static_cast<int>(w), static_cast<int>(h));
        static detail::st_arguments<value_type> arg(w, h);
#if SROOK_CPLUSPLUS == SROOK_CPLUSPLUS17_CONSTANT
        if (!detail::arguments.load(std::memory_order_acquire)) {
            lock_guard<mutex> lk(m_);
            if (!detail::arguments.load(std::memory_order_relaxed)) {
                detail::arguments.store(srook::addressof(arg), std::memory_order_release);
            }
        }
#else
        if (!detail::arguments.load(std::memory_order_consume)) {
            lock_guard<mutex> lk(m_);
            if (!detail::arguments.load(std::memory_order_relaxed)) {
                detail::arguments.store(srook::addressof(arg), std::memory_order_release);
            }
        }
#endif
    }

    template <class... Ts>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
    enable_if<type_traits::detail::Land<is_same<argument_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type>...>::value>::type 
    display(Ts&&... ts)
    {
        glutCreateWindow(title_);
        detail::arguments.load(std::memory_order_relaxed)->dots.reserve(sizeof...(ts));
#if SROOK_CPP_FOLD_EXPRESSIONS
        (detail::arguments.load(std::memory_order_relaxed)->dots.push_back(ts), ...);
#else
        nofold::f(srook::forward<Ts>(ts)...);
#endif
        glutDisplayFunc(srook::io2d::glut::utility::gsline::disp);
    }

    SROOK_FORCE_INLINE void loop() const SROOK_NOEXCEPT_TRUE { glutMainLoop(); }
private:
#if !SROOK_CPP_FOLD_EXPRESSIONS
    struct nofold {
        static SROOK_FORCE_INLINE void f() {}

        template <class U, class... Us>
        static void f(U&& u, Us&&... us)
        {
            detail::arguments.load(std::memory_order_relaxed)->dots.push_back(u);
            f(srook::forward<Us>(us)...);
        }
    };
#endif

    static void disp()
    {
        glClearColor(1, 1, 1, 0);
        glOrtho(
            -detail::arguments.load(std::memory_order_relaxed)->w_, 
            detail::arguments.load(std::memory_order_relaxed)->w_, 
            -detail::arguments.load(std::memory_order_relaxed)->h_, 
            detail::arguments.load(std::memory_order_relaxed)->h_, -1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(1);
        
        for (auto&& val : detail::arguments.load(std::memory_order_relaxed)->dots) odots(val);
        glFlush();
    }
    
    SROOK_FORCE_INLINE static void odots(const argument_type& arg) SROOK_NOEXCEPT_TRUE
    {
        for (auto&& r : srook::math::geometry::algorithm::line::straight::points(arg.first, arg.second)()) putdots(r.x(), r.y());
    }

    SROOK_FORCE_INLINE static void putdots(value_type x, value_type y) SROOK_NOEXCEPT_TRUE
    {
        glBegin(GL_POINTS);
        glColor4f(0, 0, 0, 0.4);
        glVertex2i(x, y);
        glEnd();
    }

    const char* title_;
    static SROOK_INLINE_VARIABLE mutex m_;
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
