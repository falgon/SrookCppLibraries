#ifndef INCLUDED_SROOK_UTILITY_MOVE_HPP
#define INCLUDED_SROOK_UTILITY_MOVE_HPP
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/attribute/deprecated.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/type_traits/remove_reference.hpp>
#include <srook/utility/detail/non_support_move_semantics.hpp>

namespace srook {
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT

DEF_MOVE_SEMANTICS_UTILITIES(move)

#else

template<typename T>
SROOK_CONSTEXPR typename srook::remove_reference<T>::type&& move(T&& t) SROOK_NOEXCEPT_TRUE
{ 
	return static_cast<typename srook::remove_reference<T>::type&&>(t); 
}

#endif

SROOK_INLINE_NAMESPACE_END
} // namespace utility

using utility::move;

} // namespace srook
#endif
