// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_THREAD_DETAIL_LOCK_TAGS_HPP
#define INCLUDED_SROOK_THREAD_DETAIL_LOCK_TAGS_HPP

#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature.hpp>
#include <srook/config/attribute/visibility.hpp>

namespace srook {
namespace mutexes {
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
} // namespace mutex

using mutexes::defer_lock_t;
using mutexes::defer_lock;
using mutexes::try_to_lock_t;
using mutexes::try_to_lock;
using mutexes::adopt_lock_t;
using mutexes::adopt_lock;

} // namespace srook

#endif
