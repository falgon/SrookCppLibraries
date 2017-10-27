#ifndef INCLUDED_SROOK_UTILITY_MOVE_IF_NOEXCEPT_HPP
#define INCLUDED_SROOK_UTILITY_MOVE_IF_NOEXCEPT_HPP
#include <srook/utility/move.hpp>
#include <srook/type_traits/is_nothrow_move_constructible.hpp>
#include <srook/type_traits/is_copy_constructible.hpp>
namespace srook {
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT

DEF_MOVE_SEMANTICS_UTILITIES(move_if_noexcept)

#else

namespace detail {

template<typename T>
struct move_if_noexcept_cond 
: public type_traits::detail::Land<type_traits::detail::Lnot<is_nothrow_move_constructible<T>>, is_copy_constructible<T>>::type {};

} // namespace detail

template<typename T>
SROOK_CONSTEXPR typename conditional<detail::move_if_noexcept_cond<T>::value, const T&, T&&>::type
move_if_noexcept(T& x) SROOK_NOEXCEPT_TRUE
{
	return srook::move(x); 
}

#endif

SROOK_INLINE_NAMESPACE_END
} // namespace utility

using utility::move_if_noexcept;

} // namespace srook

#endif
