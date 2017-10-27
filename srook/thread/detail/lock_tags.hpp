// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_THREAD_DETAIL_LOCK_TAGS_HPP
#define INCLUDED_SROOK_THREAD_DETAIL_LOCK_TAGS_HPP

#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/default.hpp>
#include <srook/config/feature/explicit.hpp>
#include <srook/config/attribute/visibility.hpp>

namespace srook {
namespace thread {
SROOK_INLINE_NAMESPACE(v1)

struct SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT defer_lock_t {
    SROOK_EXPLICIT defer_lock_t() SROOK_DEFAULT
};
struct SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT try_to_lock_t {
    SROOK_EXPLICIT try_to_lock_t() SROOK_DEFAULT
};
struct SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT adopt_lock_t {
    SROOK_EXPLICIT adopt_lock_t() SROOK_DEFAULT
};
#        if !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
extern const defer_lock_t defer_lock;
extern const try_to_lock_t try_to_lock;
extern const adopt_lock_t adopt_lock;
#        else
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR defer_lock_t defer_lock{};
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR try_to_lock_t try_to_lock{};
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR adopt_lock_t adopt_lock{};
#        endif

SROOK_INLINE_NAMESPACE_END
} // namespace thread

using thread::defer_lock_t;
using thread::defer_lock;
using thread::try_to_lock_t;
using thread::try_to_lock;
using thread::adopt_lock_t;
using thread::adopt_lock;

} // namespace srook

#endif
