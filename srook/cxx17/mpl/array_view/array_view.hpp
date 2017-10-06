#ifndef INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_ARRAY_VIEW_HPP
#define INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_ARRAY_VIEW_HPP
#include <srook/config/feature/constexpr.hpp> 
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/libraries/optional.hpp>
#include <srook/config/require.hpp>
#include <srook/type_traits/remove_pointer.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/is_pointer.hpp>
#include <type_traits>
#include <srook/cxx17/mpl/array_view/core/array_view_declare.hpp>
#include <srook/cxx17/mpl/array_view/algorithm/substr.hpp>
#include <array>
#include <iostream>
#include <string>
#include <string_view>

namespace srook {
namespace meta {
SROOK_INLINE_NAMESPACE(cxx17)
SROOK_INLINE_NAMESPACE(mpl)
SROOK_INLINE_NAMESPACE(v1)

template <auto p, std::size_t Size>
struct basic_array_view<p, Size, false> : detail::basic_array_view_impl<p, Size> {
	static_assert(is_pointer_v<decltype(p)>, "p must be a pointer");

	typedef detail::basic_array_view_impl<p, Size> basic_type;
	typedef typename basic_type::value_type value_type;
	typedef typename basic_type::pointer pointer;
	typedef typename basic_type::const_pointer const_pointer;
	typedef typename basic_type::reference reference;
	typedef typename basic_type::const_reference const_reference;
	typedef typename basic_type::size_type size_type;
	typedef typename basic_type::element_type element_type;
	typedef typename basic_type::result_type result_type;
	typedef basic_array_view type;
};

template <auto p, std::size_t Size>
struct basic_array_view<p, Size, true> : detail::basic_array_view_impl<p, Size> {
	static_assert(is_pointer_v<decltype(p)>, "p must be a pointer");

	typedef detail::basic_array_view_impl<p, Size> basic_type;
	typedef typename basic_type::value_type value_type;
	typedef typename basic_type::pointer pointer;
	typedef typename basic_type::const_pointer const_pointer;
	typedef typename basic_type::reference reference;
	typedef typename basic_type::const_reference const_reference;
	typedef typename basic_type::size_type size_type;
	typedef typename basic_type::element_type element_type;
	typedef typename basic_type::result_type result_type;
	typedef basic_array_view type;
	static SROOK_CONSTEXPR size_type npos = size_type(-1);

	template <size_type pos, size_type count = npos>
	using substr_type = typename array_view_algorithm::substr<type, pos, count>::type;

	operator std::string() const SROOK_NOEXCEPT_TRUE
	{ 
		return std::string{type::data(), type::data() + Size};
	}

	constexpr operator std::string_view() const SROOK_NOEXCEPT_TRUE
	{
		return {type::data(), Size};
	}
	
	friend std::ostream& operator<<(std::ostream& os, const type&)
	{
		return os.write(type::data(), Size);
	}
};

SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END

template <auto p, std::size_t Size = 0>
using array_view = basic_array_view<p, Size>;

} // namespace meta
} // namespace srook

#endif
