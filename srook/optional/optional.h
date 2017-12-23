#ifndef INCLUDED_SROOK_OPTIONAL_OPTIONAL_H
#define INCLUDED_SROOK_OPTIONAL_OPTIONAL_H

#include <srook/config.hpp>
#if SROOK_HAS_INCLUDE(<optional>) && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
#   include <optional>
#   define SROOK_HAS_STD_OPTIONAL 1
#endif
#   if SROOK_HAS_INCLUDE(<boost/optional.hpp>)
#   include <boost/optional.hpp>
#   define SROOK_HAS_BOOST_OPTIONAL 1
#endif
#if SROOK_HAS_INCLUDE(<compare>) // C++20 feature
#   include <compare>
#endif

#include <srook/type_traits.hpp>
#include <srook/optional/nullopt.hpp>
#include <srook/optional/exception.hpp>
#include <initializer_list>

namespace srook {
namespace optionally {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, bool, bool>
class optional_payload;
template <class T, bool, bool>
class safe_optional_payload;

} // namespace detail

using detail::optional_payload;
using detail::safe_optional_payload;

template <class, template <class, bool, bool> class = optional_payload>
class optional;

template <class T>
SROOK_CONSTEXPR optional<SROOK_DEDUCED_TYPENAME decay<T>::type> make_optional(T&&);

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT && SROOK_CPP_RVALUE_REFERENCES
template <class T, class... Args>
SROOK_CONSTEXPR optional<T> make_optional(Args&&...);

template <class T, class U, class... Args>
SROOK_CONSTEXPR optional<T> make_optional(std::initializer_list<U>, Args&&...);
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace optionally

using optionally::make_optional;
using optionally::optional;

} // namespace srook
#endif
