// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_BIT_BIT_CAST_HPP
#define INCLUDED_SROOK_BIT_BIT_CAST_HPP

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <type_traits>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/cstring/memcpy.hpp>
#include <srook/type_traits.hpp>
#include <srook/memory.hpp>

namespace srook {
namespace bit {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, class U>
struct ov_participate 
    : bool_constant<sizeof(T) == sizeof(U) || type_traits::detail::Land<std::is_trivially_copyable<T>, std::is_trivially_copyable<U>>::value> {};

template <class T>
struct only_constexpr_requirements
    : type_traits::detail::Land<
        type_traits::detail::Lnot<is_union<T>>, 
        type_traits::detail::Lnot<is_pointer<T>>, 
        type_traits::detail::Lnot<is_member_pointer<T>>, 
        type_traits::detail::Lnot<is_volatile<T>>
      > {};

template <class T, class U>
struct ov_participate_with_constant 
    : type_traits::detail::Land<only_constexpr_requirements<T>, only_constexpr_requirements<U>, ov_participate<T, U>> {};

} // namespace detail

template <typename To, typename From>
#if SROOK_HAS_CONCEPTS
requires detail::only_constexpr_requirements<To>::value && detail::only_constexpr_requirements<From>::value && detail::ov_participate<To, From>::value // more constraints
SROOK_CONSTEXPR To
#else
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<detail::ov_participate_with_constant<To, From>::value, To>::type
#endif
bit_cast(const From& from) SROOK_NOEXCEPT_TRUE
{
    SROOK_DEDUCED_TYPENAME aligned_storage<sizeof(To), SROOK_ALIGN_OF(To)>::type storage{};
    srook::memcpy(&storage, &from, sizeof(To));
    return reinterpret_cast<To&>(storage);
}

template <typename To, typename From>
#if SROOK_HAS_CONCEPTS
requires detail::ov_participate<To, From>::value SROOK_FORCE_INLINE To
#else
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
enable_if<
    type_traits::detail::Land<
        detail::ov_participate<To, From>,
        type_traits::detail::Lnot<detail::only_constexpr_requirements<To>>,
        type_traits::detail::Lnot<detail::only_constexpr_requirements<From>>
    >::value,
    To
>::type
#endif
bit_cast(const From& from) SROOK_NOEXCEPT_TRUE
{
    SROOK_DEDUCED_TYPENAME aligned_storage<sizeof(To), SROOK_ALIGN_OF(To)>::type storage{};
    srook::memcpy(&storage, srook::addressof(from), sizeof(To));
    return reinterpret_cast<To&>(storage);
}

SROOK_INLINE_NAMESPACE_END
} // namespace bit
} // namespace srook
#endif
#endif
