// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_UTILITY_ENABLE_COPY_MOVE_HPP
#define INCLUDED_SROOK_UTILITY_ENABLE_COPY_MOVE_HPP

#include <srook/config/cpp_predefined.hpp>
#include <srook/utility/void_t.hpp>
#include <srook/config/feature.hpp>

namespace srook {
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

template <bool, bool, bool, bool, class = SROOK_DEDUCED_TYPENAME voider<void>::type>
struct enable_copy_move;

#define DEF_ENABLE_COPY_MOVE(B1, B2, B3, B4, DEFAULT_OR_DELETE1, DEFAULT_OR_DELETE2, DEFAULT_OR_DELETE3, DEFAULT_OR_DELETE4, DEFAULT_OR_DELETE5)\
template <class Tag>\
struct enable_copy_move<B1, B2, B3, B4, Tag> {\
	SROOK_CONSTEXPR enable_copy_move() SROOK_NOEXCEPT_TRUE DEFAULT_OR_DELETE1\
	SROOK_CONSTEXPR enable_copy_move(const enable_copy_move&) SROOK_NOEXCEPT_TRUE DEFAULT_OR_DELETE2\
	SROOK_CONSTEXPR enable_copy_move(enable_copy_move&&) SROOK_NOEXCEPT_TRUE DEFAULT_OR_DELETE3\
	enable_copy_move& operator=(const enable_copy_move&) SROOK_NOEXCEPT_TRUE DEFAULT_OR_DELETE4\
	enable_copy_move& operator=(enable_copy_move&&) SROOK_NOEXCEPT_TRUE DEFAULT_OR_DELETE5\
}

DEF_ENABLE_COPY_MOVE(false, true, true, true, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_DEFAULT, SROOK_DEFAULT, SROOK_DEFAULT);
DEF_ENABLE_COPY_MOVE(true, false, true, true, SROOK_DEFAULT, SROOK_DEFAULT, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_DEFAULT);
DEF_ENABLE_COPY_MOVE(false, false, true, true, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_DEFAULT);
DEF_ENABLE_COPY_MOVE(true, true, false, true, SROOK_DEFAULT, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_DEFAULT, SROOK_DEFAULT);
DEF_ENABLE_COPY_MOVE(false, true, false, true, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_EQ_DELETE, SROOK_DEFAULT, SROOK_DEFAULT);
DEF_ENABLE_COPY_MOVE(true, false, false, true, SROOK_DEFAULT, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_EQ_DELETE, SROOK_DEFAULT);
DEF_ENABLE_COPY_MOVE(false, false, false, true, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_EQ_DELETE, SROOK_EQ_DELETE, SROOK_DEFAULT);
DEF_ENABLE_COPY_MOVE(true, true, true, false, SROOK_DEFAULT, SROOK_DEFAULT, SROOK_DEFAULT, SROOK_DEFAULT, SROOK_EQ_DELETE);
DEF_ENABLE_COPY_MOVE(false, true, true, false, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_DEFAULT, SROOK_DEFAULT, SROOK_EQ_DELETE);
DEF_ENABLE_COPY_MOVE(true, false, true, false, SROOK_DEFAULT, SROOK_DEFAULT, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_EQ_DELETE);
DEF_ENABLE_COPY_MOVE(false, false, true, false, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_EQ_DELETE);
DEF_ENABLE_COPY_MOVE(true, true, false, false, SROOK_DEFAULT, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_DEFAULT, SROOK_EQ_DELETE);
DEF_ENABLE_COPY_MOVE(false, true, false, false, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_EQ_DELETE, SROOK_DEFAULT, SROOK_EQ_DELETE);
DEF_ENABLE_COPY_MOVE(true, false, false, false, SROOK_DEFAULT, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_EQ_DELETE, SROOK_EQ_DELETE);
DEF_ENABLE_COPY_MOVE(false, false, false, false, SROOK_DEFAULT, SROOK_EQ_DELETE, SROOK_EQ_DELETE, SROOK_EQ_DELETE, SROOK_EQ_DELETE);
#undef DEF_ENABLE_COPY_MOVE

template <class = SROOK_DEDUCED_TYPENAME voider<void>::type>
struct disable_special_functions {
	SROOK_CONSTEXPR disable_special_functions() SROOK_NOEXCEPT_TRUE SROOK_EQ_DELETE
	SROOK_CONSTEXPR disable_special_functions(const disable_special_functions&) SROOK_NOEXCEPT_TRUE SROOK_EQ_DELETE
	SROOK_CONSTEXPR disable_special_functions(disable_special_functions&&) SROOK_NOEXCEPT_TRUE SROOK_EQ_DELETE
	disable_special_functions& operator=(const disable_special_functions&) SROOK_NOEXCEPT_TRUE SROOK_EQ_DELETE
	disable_special_functions& operator=(disable_special_functions&&) SROOK_NOEXCEPT_TRUE SROOK_EQ_DELETE
};


SROOK_INLINE_NAMESPACE_END
} // namespace utility

using utility::enable_copy_move;
using utility::disable_special_functions;

} // namespace srook
#endif
