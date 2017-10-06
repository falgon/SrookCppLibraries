#ifndef INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_ALGORITHM_FRONT_HPP
#define INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_ALGORITHM_FRONT_HPP
#include <srook/cxx17/mpl/array_view/core/basic_array_view_declare.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/libraries/nullptr.hpp>
#include <srook/config/libraries/optional.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/remove_pointer.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/remove_reference.hpp>

namespace srook {
namespace meta {
SROOK_INLINE_NAMESPACE(cxx17)
SROOK_INLINE_NAMESPACE(mpl)
SROOK_INLINE_NAMESPACE(v1)
namespace array_view_algorithm{
namespace detail {

template <class> struct front_impl;
template <auto Src, std::size_t Size>
struct front_impl<meta::detail::basic_array_view_impl<Src, Size>> : integral_constant<remove_pointer_t<remove_cv_t<remove_reference_t<decltype(Src)>>>, *Src> {};

} // namespace detail

template <class T>
struct front : detail::front_impl<T> {};

} // namespace array_view_algorithm
SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END
} // namespace meta
} // namespace srook

#endif
