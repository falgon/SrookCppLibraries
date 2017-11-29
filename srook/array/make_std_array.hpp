#ifndef INCLUDED_SROOK_ARRAY_MAKE_ARRAY_HPP
#define INCLUDED_SROOK_ARRAY_MAKE_ARRAY_HPP
#include <array>
#include <functional>
#include <srook/config.hpp>
#include <srook/type_traits.hpp>

namespace srook {
namespace fundamental {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class>
struct is_ref_wrapper : SROOK_FALSE_TYPE {};
template <class T>
struct is_ref_wrapper<std::reference_wrapper<T> > : SROOK_TRUE_TYPE {};

template <class T>
using not_ref_wrapper = srook::negation<is_ref_wrapper<SROOK_DEDUCED_TYPENAME decay<T>::type > >;

template <class D, class...>
struct return_type_helper {
    using type = D;
};
template <class... Ts>
struct return_type_helper<void, Ts...> : std::common_type<Ts...> {
    SROOK_STATIC_ASSERT(conjunction<not_ref_wrapper<Ts>...>::value, "Ts cannot contain reference_wrappers when D is void");
};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class D, class... Ts>
using return_type = std::array<SROOK_DEDUCED_TYPENAME return_type_helper<D, Ts...>::type, sizeof...(Ts)>;
#endif

} // namespace detail

template <class D = void, class... Ts>
SROOK_CONSTEXPR detail::return_type<D, Ts...> make_array(Ts&&... t) 
SROOK_NOEXCEPT(conjunction<is_nothrow_constructible<Ts>...>::value)
{
    return {std::forward<Ts>(t)...};
}

SROOK_INLINE_NAMESPACE_END
} // namespace fundamental
} // namespace srook

#endif
