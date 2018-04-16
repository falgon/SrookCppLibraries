// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_IO2D_THIRD_PARTY_OPENCV_GLUT_UTILITY_PAINTER_HPP
#define INCLUDED_SROOK_IO2D_THIRD_PARTY_OPENCV_GLUT_UTILITY_PAINTER_HPP

#include <srook/io2d/third_party/opengl/glut/detail/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/io2d/third_party/opengl/glut/detail/globalp.hpp>
#include <srook/io2d/third_party/opengl/glut/utility/params.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/type_traits/detail/has_type_gen.hpp>
#include <srook/mutex/mutexes/mutex.hpp>
#include <srook/mutex/guards/lock_guard.hpp>
#include <srook/mutex/once.hpp>
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

SROOK_TT_DEF_HAS_TYPE_IMPL(point_type);
SROOK_TT_DEF_HAS_TYPE(point_type);

SROOK_TT_DEF_HAS_TYPE_IMPL(vector_type);
SROOK_TT_DEF_HAS_TYPE(vector_type);

} // namespace detail

template <class PaintAlgorithm>
class painter {
public:
    typedef double value_type;
    typedef PaintAlgorithm paint_algo_type;
private:
    typedef ::srook::io2d::glut::detail::globalp<PaintAlgorithm> gbp_type;
public:
    typedef srook::math::geometry::fundamental::point<value_type> point_type;
    typedef SROOK_DEDUCED_TYPENAME PaintAlgorithm::argument_type argument_type;

    SROOK_FORCE_INLINE painter(const params& p, std::size_t granularity = 1024)
        : displayed(false), granularity_(granularity)
    {
        static gbp_type arg(p);
#if SROOK_CPLUSPLUS == SROOK_CPLUSPLUS17_CONSTANT
#   define SROOK_PAINTER_MEMORY_ORDER std::memory_order_acquire
#else
#   define SROOK_PAINTER_MEMORY_ORDER std::memory_order_consume
#endif
        if (!gbp_type::gpp.load(SROOK_PAINTER_MEMORY_ORDER)) {
            srook::lock_guard<mutex> lk(m_);
            if (!gbp_type::gpp.load(std::memory_order_relaxed)) {
                gbp_type::gpp.store(srook::addressof(arg), std::memory_order_release);
            }
        }
        srook::call_once(once0, init, gbp_type::gpp.load(std::memory_order_relaxed));
    }

    template <class... Ts>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
    enable_if<type_traits::detail::Land<is_same<argument_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type>...>::value>::type 
    display(Ts&&... ts)
    {
        if (!displayed.load(SROOK_PAINTER_MEMORY_ORDER)) {
            srook::lock_guard<mutex> lk(m_);
            if (!displayed.load(std::memory_order_relaxed)) {
                glutCreateWindow(gbp_type::gpp.load(std::memory_order_relaxed)->title());
                SROOK_DEDUCED_TYPENAME gbp_type::dots_type& dots = gbp_type::gpp.load(std::memory_order_relaxed)->dots();
                dots.reserve(sizeof...(ts));
#if SROOK_CPP_FOLD_EXPRESSIONS
                (dots.push_back(ts), ...);
#else
                nofold::f(dots, srook::forward<Ts>(ts)...);
#endif
                glutDisplayFunc(disp);
                glutReshapeFunc(resize);
                displayed.store(true, std::memory_order_release);
            }
        }
    }
#undef SROOK_PAINTER_MEMORY_ORDER

    SROOK_FORCE_INLINE void loop() const SROOK_NOEXCEPT_TRUE 
    { 
        srook::call_once(once1, ::glutMainLoop); 
    }
private:
#if !SROOK_CPP_FOLD_EXPRESSIONS
    struct nofold {
        static SROOK_FORCE_INLINE void f(SROOK_DEDUCED_TYPENAME gbp_type::dots_type&) SROOK_NOEXCEPT_TRUE {}

        template <class U, class... Us>
        static void f(SROOK_DEDUCED_TYPENAME gbp_type::dots_type& dots, U&& u, Us&&... us)
        {
            dots.push_back(u);
            f(srook::forward<Us>(us)...);
        }
    };
#endif

    static void disp()
    {
        glClearColor(1, 1, 1, 0);
        auto wsize = gbp_type::gpp.load(std::memory_order_relaxed)->winsize();

        glOrtho(-wsize.first, wsize.first, -wsize.second, wsize.second, -1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(1);
        
        typedef SROOK_DEDUCED_TYPENAME conditional<
            ::srook::type_traits::detail::Land<
                ::srook::type_traits::detail::Lnot<detail::has_vector_type<paint_algo_type>>,
                detail::has_point_type<paint_algo_type>
            >::value,
            simple_odots,
            parametric
        >::type output;
        for (auto&& val : gbp_type::gpp.load(std::memory_order_relaxed)->dots()) {
            output::do_output(srook::forward<SROOK_DECLTYPE(val)>(val));
        }

        glFlush();
    }

    static void resize(int w, int h)
    {
        glViewport(0, 0, w, h);
        glLoadIdentity();
        glOrtho(-w/400, w/400, -h/400, h/400, -1.0, 1.0);
    }

    struct simple_odots {
        SROOK_FORCE_INLINE static void do_output(const argument_type& arg) SROOK_NOEXCEPT_TRUE
        {
            for (auto&& r : paint_algo_type(arg.first, arg.second)()) putdots(r.x(), r.y());
        }
    };

    struct parametric {
        SROOK_FORCE_INLINE static void do_output(const argument_type& arg)
        {
            auto t = gbp_type::gpp.load(std::memory_order_relaxed)->granularity();
            for (auto&& r : paint_algo_type(std::get<0>(arg), std::get<1>(arg), std::get<2>(arg), std::get<3>(arg), t)()) putdots(r.x() * 300, r.y() * 300); // TODO
        }
    };
        
    SROOK_FORCE_INLINE static void putdots(value_type x, value_type y) SROOK_NOEXCEPT_TRUE
    {
        glBegin(GL_POINTS);
        glColor4f(0, 0, 0, 1.f);
        vertex2type(x, y, is_floating_point<value_type>{});
        glEnd();
    }

    SROOK_FORCE_INLINE static void vertex2type(value_type x, value_type y, SROOK_TRUE_TYPE) SROOK_NOEXCEPT_TRUE
    {
        vertex2floating(x, y, bool_constant<(sizeof x > 4)>{});
    }

    SROOK_FORCE_INLINE static void vertex2floating(value_type x, value_type y, SROOK_TRUE_TYPE) SROOK_NOEXCEPT_TRUE
    {
        glVertex2d(x, y);
    }

    SROOK_FORCE_INLINE static void vertex2floating(value_type x, value_type y, SROOK_FALSE_TYPE) SROOK_NOEXCEPT_TRUE
    {
        glVertex2f(x, y);
    }

    SROOK_FORCE_INLINE static void vertex2type(value_type x, value_type y, SROOK_FALSE_TYPE) SROOK_NOEXCEPT_TRUE
    {
        glVertex2i(static_cast<int>(x), static_cast<int>(y));
    }

    SROOK_FORCE_INLINE static void init(const gbp_type* p) SROOK_NOEXCEPT_TRUE
    {
        auto args = p->args();
        glutInit(&args.first, args.second);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

        auto pos = p->position();
        glutInitWindowPosition(static_cast<int>(pos.first), static_cast<int>(pos.second));

        auto wsize = p->winsize();
        glutInitWindowSize(static_cast<int>(wsize.first), static_cast<int>(wsize.second));
    }

    static SROOK_INLINE_VARIABLE srook::mutex m_;
    static SROOK_INLINE_VARIABLE srook::once_flag once0, once1;
    std::size_t granularity_;
    std::atomic<bool> displayed;
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
