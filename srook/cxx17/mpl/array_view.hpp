#ifndef INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_ARRAY_VIEW_HPP
#define INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_ARRAY_VIEW_HPP
#include <srook/config/feature/constexpr.hpp> 
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/libraries/optional.hpp>
#include <srook/config/require.hpp>
#include <srook/type_traits/remove_pointer.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <type_traits>

#include <srook/cxx17/mpl/array_view/core/array_view_declare.hpp>
#include <srook/cxx17/mpl/array_view/algorithm/at.hpp>
#include <srook/cxx17/mpl/array_view/algorithm/front.hpp>
#include <srook/cxx17/mpl/array_view/algorithm/back.hpp>

namespace srook {
namespace cxx17 {
SROOK_INLINE_NAMESPACE(mpl)
SROOK_INLINE_NAMESPACE(v1)

template <auto* Source, std::size_t Size>
struct array_view {
	// types
	typedef remove_pointer_t<decltype(Source)> value_type;
	typedef value_type pointer;
	typedef const pointer const_pointer;
	typedef remove_pointer_t<value_type>& reference;
	typedef reference const_reference;
	typedef decltype(Size) size_type;
	typedef conditional_t<static_cast<bool>(Size), SROOK_OPTIONAL<value_type>, value_type> element_type;
	typedef const element_type result_type;
	typedef array_view type;

	// common functions
	SROOK_CONSTEXPR array_view() = default;

	static SROOK_CONSTEXPR decltype(auto) value = Source;
	static SROOK_CONSTEXPR std::size_t size_value = Size;
	static SROOK_CONSTEXPR decltype(auto) data() SROOK_NOEXCEPT_TRUE { return value; }
	static SROOK_CONSTEXPR std::size_t size() SROOK_NOEXCEPT_TRUE { return size_value; }
	SROOK_CONSTEXPR std::size_t instance_size() const SROOK_NOEXCEPT_TRUE { return type::size(); }
	SROOK_CONSTEXPR std::size_t instance_length() const SROOK_NOEXCEPT_TRUE { return type::length(); }
	static SROOK_CONSTEXPR std::size_t length() SROOK_NOEXCEPT_TRUE { return size(); }
	SROOK_CONSTEXPR operator value_type() const SROOK_NOEXCEPT_TRUE { return value; }
	SROOK_CONSTEXPR value_type operator()() const SROOK_NOEXCEPT_TRUE { return value; }
		
	// element accesses
	template <std::size_t Index>
	using at_type = array_view_algorithm::at<type, Index>;
	template <std::size_t Index>
	static SROOK_CONSTEXPR element_type at_v = at_type<Index>::value;
	template <std::size_t Index>
	static SROOK_CONSTEXPR element_type at() SROOK_NOEXCEPT_TRUE { return at_type<Index>::value; }
	template <class Integral, Integral Index, REQUIRES(is_integral_v<Integral>)>
	static SROOK_CONSTEXPR element_type at(integral_constant<Integral, Index>) SROOK_NOEXCEPT_TRUE { return at_type<Index>::value; }
	template <class Integral, Integral Index, REQUIRES(is_integral_v<Integral>)>
	static SROOK_CONSTEXPR element_type at(std::integral_constant<Integral, Index>) SROOK_NOEXCEPT_TRUE { return at_type<Index>::value; }

	template <std::size_t Index>
	SROOK_CONSTEXPR element_type instance_at() const SROOK_NOEXCEPT_TRUE { return at_type<Index>::value; }
	template <class Integral, Integral Index, REQUIRES(is_integral_v<Integral>)>
	SROOK_CONSTEXPR element_type instance_at(integral_constant<Integral, Index>) const SROOK_NOEXCEPT_TRUE { return at_type<Index>::value; }
	template <class Integral, Integral Index, REQUIRES(is_integral_v<Integral>)>
	SROOK_CONSTEXPR element_type instance_at(std::integral_constant<Integral, Index>) const SROOK_NOEXCEPT_TRUE { return at_type<Index>::value; }

	template <class Integral, Integral Index, REQUIRES(is_integral_v<Integral>)>
	SROOK_CONSTEXPR element_type operator[](integral_constant<Integral, Index>) const SROOK_NOEXCEPT_TRUE { return at_type<Index>::value; }
	template <class Integral, Integral Index, REQUIRES(is_integral_v<Integral>)>
	SROOK_CONSTEXPR element_type operator[](std::integral_constant<Integral, Index>) const SROOK_NOEXCEPT_TRUE { return at_type<Index>::value; }

	using front_type = array_view_algorithm::front<type>;
	static SROOK_CONSTEXPR const_reference front_v = front_type::value;
	static SROOK_CONSTEXPR const_reference front() SROOK_NOEXCEPT_TRUE { return front_type::value; } 
	SROOK_CONSTEXPR const_reference instance_front() const SROOK_NOEXCEPT_TRUE { return front_type::value; }

	using back_type = array_view_algorithm::back<type>;
	static SROOK_CONSTEXPR const_reference back_v = back_type::value;
	static SROOK_CONSTEXPR const_reference back() SROOK_NOEXCEPT_TRUE { return back_type::value; }
	SROOK_CONSTEXPR const_reference instance_back() const SROOK_NOEXCEPT_TRUE { return back_type::value; }
};

SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END
} // namespace cxx17
} // namespace srook

#endif
