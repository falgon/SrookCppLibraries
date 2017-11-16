// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_UTILITY_NONCOPYABLE_HPP
#define INCLUDED_SROOK_UTILITY_NONCOPYABLE_HPP

#include <srook/utility/enable_copy_move.hpp>
/*#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/feature/default.hpp>
#include <srook/config/feature/delete.hpp>
#include <srook/config/feature/constexpr.hpp>*/

namespace srook {
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
class noncopyable : private enable_copy_move<false, false, true, true, noncopyable<T> > {
/*protected:
	SROOK_CONSTEXPR noncopyable() SROOK_NOEXCEPT_TRUE SROOK_DEFAULT
	~noncopyable() SROOK_NOEXCEPT_TRUE SROOK_DEFAULT
private:
	noncopyable(const noncopyable&) SROOK_NOEXCEPT_TRUE SROOK_EQ_DELETE
	T& operator=(const T&) SROOK_NOEXCEPT_TRUE SROOK_EQ_DELETE*/
};

SROOK_INLINE_NAMESPACE_END
} // utility

using utility::noncopyable;

} // srook

#endif
