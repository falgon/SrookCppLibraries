// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_UTILITY_AGGREGATE_ADAPTER_HPP
#define INCLUDED_SROOK_MEMORY_UTILITY_AGGREGATE_ADAPTER_HPP

#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/type_traits/is_nothrow_move_constructible.hpp>
#include <srook/type_traits/conjunction.hpp>
#include <srook/utility/forward.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>

namespace srook {
namespace memory {
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

#if (SROOK_CPLUSPLUS11_CONSTANT <= SROOK_CPLUSPLUS) || SROOK_CPP_VARIADIC_TEMPLATES
template <class T>
struct aggregate_adapter : public T {
	template <class... Args>
	SROOK_CONSTEXPR aggregate_adapter(Args&&... args) 
	SROOK_NOEXCEPT(conjunction<is_nothrow_move_constructible<Args>...>::value)
	: T{ forward<Args>(args)... } {}
};
#else
#	error Variadic templates is not supported in this environment.
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace utility

using utility::aggregate_adapter;

} // namespace memoru

using memory::aggregate_adapter;

} // namespace srook

#endif
