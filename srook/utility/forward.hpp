#ifndef INCLUDED_SROOK_UTILITY_FORWARD_HPP
#define INCLUDED_SROOK_UTILITY_FORWARD_HPP
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/remove_reference.hpp>
#include <srook/type_traits/is_lvalue_reference.hpp>
#include <srook/utility/detail/non_support_move_semantics.hpp>

namespace srook {
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT

DEF_FORWARD_SEMANTICS_UTILITIES(forward)

#else

template <typename T>
SROOK_CONSTEXPR T&& forward(typename remove_reference<T>::type& t) SROOK_NOEXCEPT_TRUE
{
	return static_cast<T&&>(t);
}

template <typename T>
SROOK_CONSTEXPR T&& forward(typename remove_reference<T>::type&& t) SROOK_NOEXCEPT_TRUE
{
	static_assert(!std::is_lvalue_reference<T>::value,"template argument substituting T is an lvalue reference type");
	return static_cast<T&&>(t);
}

#endif

SROOK_INLINE_NAMESPACE_END
} // namespace utility

using utility::forward;

} // namespace srook
#endif
