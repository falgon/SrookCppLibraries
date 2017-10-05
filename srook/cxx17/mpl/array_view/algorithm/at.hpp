#ifndef INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_ALGORITHM_AT_HPP
#define INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_ALGORITHM_AT_HPP
#include <srook/cxx17/mpl/array_view/core/array_view_declare.hpp>
#include <srook/config/feature/constexpr.hpp> 
#include <srook/config/libraries/nullptr.hpp>
#include <srook/config/libraries/optional.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/remove_pointer.hpp>

namespace srook {
namespace cxx17 {
SROOK_INLINE_NAMESPACE(mpl)
SROOK_INLINE_NAMESPACE(v1)
namespace array_view_algorithm{
namespace detail {

template <auto, std::size_t, std::size_t, class = SROOK_NULLPTR_T> struct at_impl_;
template <auto Src, std::size_t Size, std::size_t I>
struct at_impl_<Src, Size, I, enable_if_t<(Size > I), SROOK_NULLPTR_T>> {
	static SROOK_CONSTEXPR SROOK_OPTIONAL<remove_pointer_t<decltype(Src)>> value = *(Src + I);
};
template <auto Src, std::size_t Size, std::size_t I>
struct at_impl_<Src, Size, I, enable_if_t<(Size <= I), SROOK_NULLPTR_T>> {
	static SROOK_CONSTEXPR SROOK_OPTIONAL<remove_pointer_t<decltype(Src)>> value = SROOK_NULLOPT;
};

template <class, std::size_t> struct at_impl;
template <auto Src, std::size_t Size, std::size_t I>
struct at_impl<array_view<Src, Size>, I> : at_impl_<Src, Size, I> {};
template <auto Src, std::size_t I>
struct at_impl<array_view<Src, 0>, I> {
	static constexpr remove_pointer_t<decltype(Src)> value = *(Src + I);
};

} // namespace detail

template <class T, std::size_t I>
struct at : detail::at_impl<T, I> {};

} // namespace array_view_algorithm
SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END
} // namespace cxx17
} // namespace srook

#endif
