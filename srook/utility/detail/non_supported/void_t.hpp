// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_UTILITY_DETAIL_NON_SUPPORTED_VOID_T_HPP
#define INCLUDED_SROOK_UTILITY_DETAIL_NON_SUPPORTED_VOID_T_HPP

#include <srook/config/cpp_predefined/feature_testing.hpp>

#if !SROOK_CPP_VARIADIC_TEMPLATES 
#include <srook/config/user_config.hpp>
#include <srook/config/feature.hpp>
#include <srook/preprocessor/detail/loop_comma.hpp>
#include <srook/preprocessor/detail/iterate_def.hpp>
#include <cstddef>

#define CLASS_DECL(N) class T##N
#define LOOP_CNT(N) T##N

#define EMPTY_TYPE(N)\
	template <class T, SROOK_PP_LOOP_COMMA(CLASS_DECL, N)>\
	struct Empty_type_##N {\
		SROOK_CONSTEXPR_OR_CONST std::size_t size() const SROOK_NOEXCEPT_TRUE { return N; }\
		typedef T type;\
	};

#define VOID_T_IMPL(N)\
	template <SROOK_PP_LOOP_COMMA(CLASS_DECL, N)>\
	struct void_t_impl_##N : Empty_type_##N<void, SROOK_PP_LOOP_COMMA(LOOP_CNT, N)> {};

#define VOID_T_N(N)\
	template <SROOK_PP_LOOP_COMMA(CLASS_DECL, N)>\
	struct voider_##N {\
		typedef typename utility::detail::void_t_impl_##N<SROOK_PP_LOOP_COMMA(LOOP_CNT, N)>::type type;\
	};

namespace srook {
namespace utility {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

SROOK_PP_ITERATE(EMPTY_TYPE, 32)
SROOK_PP_ITERATE(VOID_T_IMPL, 32)

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace utility

SROOK_PP_ITERATE(VOID_T_N, 32)

#undef CLASS_DECL
#undef LOOP_CNT
#undef COMMA
} // namespace srook

#endif

#endif
