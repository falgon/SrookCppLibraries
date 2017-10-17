#ifndef INCLUDED_SROOK_SYSTEM_IS_VM_HPP
#define INCLUDED_SROOK_SYSTEM_IS_VM_HPP
#include <srook/config/attribute/naked.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/libraries/byte.hpp>
#include <type_traits>
#include <cstdint>

namespace srook {
namespace experimental {
namespace system {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

#if defined(__GNUC__) || defined(__clang__)
bool redpill()
{
	std::make_signed_t<std::underlying_type_t<srook::byte>> result[(sizeof(long) == 8) ? 10 : 6];
	asm volatile (
			"sidt (%[ptr])"
			: "=m" (result)
			: [ptr] "r" (&result)
	);
	return result[(sizeof(long) == 8) ? 9 : 5] > 0xd0;
}
#else
#	error "This platform is not supported"
#endif

} // namespace detail
SROOK_INLINE_NAMESPACE_END

bool is_vm()
{
	return detail::redpill();
}

} // namespace system
} // namespace experimental
} // namespace srook

#endif
