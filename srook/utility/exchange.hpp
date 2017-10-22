#ifndef INCLUDED_SROOK_UTILITY_EXCHANGE_HPP
#define INCLUDED_SROOK_UTILITY_EXCHANGE_HPP
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/type_traits/is_nothrow_move_constructible.hpp>
#include <srook/type_traits/is_nothrow_assignable.hpp>
#include <srook/utility/forward.hpp>
#include <srook/utility/move.hpp>

namespace srook {
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

template <class T, class U = T>
inline T exchange(T& o, U&& new_value)
SROOK_NOEXCEPT(
	is_nothrow_move_constructible<T>::value && 
	is_nothrow_move_constructible<U>::value &&
	is_nothrow_assignable<T>::value
)
{
	T oldval = srook::move(o);
	o = srook::forward<U>(new_value);
	return oldval;
}

SROOK_INLINE_NAMESPACE_END
} // utility

using utility::exchange;

} // namespace srook

#endif
