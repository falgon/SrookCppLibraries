#ifndef INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_ALGORITHM_BACK_HPP
#define INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_ALGORITHM_BACK_HPP
#include <srook/cxx17/mpl/array_view/core/array_view_declare.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/libraries/nullptr.hpp>
#include <srook/config/libraries/optional.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/remove_pointer.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/remove_reference.hpp>

namespace srook {
namespace cxx17 {
SROOK_INLINE_NAMESPACE(mpl)
SROOK_INLINE_NAMESPACE(v1)
namespace array_view_algorithm{
namespace detail {

template <auto Src, std::size_t Size> 
struct back_impl_ : integral_constant<remove_cv_t<remove_reference_t<remove_pointer_t<decltype(Src)>>>, *(Src + (Size - 1))> {};

template <class> struct back_impl;
template <auto Src, std::size_t Size>
struct back_impl<array_view<Src, Size>> : back_impl_<Src, static_cast<bool>(Size) ? Size : Size + 1> {};

} // namespace detail

template <class T>
struct back : detail::back_impl<T> {};

} // namespace array_view_algorithm
SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END
} // namespace cxx17
} // namespace srook

#endif
