#ifndef INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_ALGORITHM_TO_CONTAINER_HPP
#define INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_ALGORITHM_TO_CONTAINER_HPP
#include <srook/cxx17/mpl/array_view/core/basic_array_view_declare.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/libraries/nullptr.hpp>
#include <srook/config/libraries/optional.hpp>
#include <srook/type_traits/type_constant.hpp>

namespace srook {
namespace meta {
SROOK_INLINE_NAMESPACE(cxx17)
SROOK_INLINE_NAMESPACE(mpl)
SROOK_INLINE_NAMESPACE(v1)
namespace array_view_algorithm{
namespace detail {

template <class T, template <class...> class Container>
struct to_container_impl {
	static Container<typename T::value_type> value;
};

template <class T, template<class...> class Container>
static Container<typename T::value_type> value = { T::data(), T::data() + T::size_value };

} // namespace detail

template <class T, template <class...> class Container>
struct to_container : detail::to_container_impl<T, Container> {};

} // namespace array_view_algorithm
SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END
} // namespace meta
} // namespace srook

#endif
