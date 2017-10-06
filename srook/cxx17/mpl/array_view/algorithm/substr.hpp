#ifndef INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_ALGORITHM_SUBSTR_HPP
#define INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_ALGORITHM_SUBSTR_HPP
#include <srook/cxx17/mpl/array_view/core/array_view_declare.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/libraries/nullptr.hpp>
#include <srook/config/libraries/optional.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/remove_pointer.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/remove_reference.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/conditional.hpp>
#include <algorithm>

namespace srook {
namespace meta {
SROOK_INLINE_NAMESPACE(cxx17)
SROOK_INLINE_NAMESPACE(mpl)
SROOK_INLINE_NAMESPACE(v1)
namespace array_view_algorithm{
namespace detail {

template <auto ForLazyEval>
struct Assertation {
	static_assert(ForLazyEval ? false : false, "If you do not set request length, must set size (likes array_view<T, n>) or set request length..."); 
};

template <auto Src, std::size_t Size, std::size_t pos, std::size_t count>
struct substr_impl_ : type_constant<basic_array_view<(Src + pos), std::min(Size - pos, count), true>> {};

template <class T, class SizeType, SizeType, SizeType> struct substr_impl;

template <auto Src, std::size_t Size, class SizeType, SizeType pos, SizeType count>
struct substr_impl<basic_array_view<Src, Size, true>, SizeType, pos, count> {
private:
	typedef basic_array_view<Src, Size, true> tmp_type;
public:
	typedef 
		conditional_t<
			count != tmp_type::npos, 
			typename substr_impl_<Src, Size, pos, count>::type,
			conditional_t<
				static_cast<bool>(Size), 
				typename substr_impl_<Src, Size, pos, static_cast<std::size_t>(Size - pos)>::type,
				Assertation<Size>
			>
		> 
	type;
};
	
} // namespace detail

template <class T, typename T::size_type pos, typename T::size_type count>
struct substr : type_constant<typename detail::substr_impl<T, typename T::size_type, pos, count>::type> {};

} // namespace array_view_algorithm
SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END
} // namespace meta
} // namespace srook

#endif
