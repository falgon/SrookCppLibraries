#ifndef INCLUDED_SROOK_MPL_UTILITY_TO_DIGIT_HPP
#define INCLUDED_SROOK_MPL_UTILITY_TO_DIGIT_HPP
#include<type_traits>
#include<srook/config/require.hpp>
#include<srook/config/libraries/optional.hpp>
#include<srook/config/compiler.hpp>

namespace srook{
inline namespace mpl{
inline namespace v1{

namespace detail{
// explicitly code for some characters code...

template<char>
struct ctoi{
	static constexpr SROOK_OPTIONAL<unsigned short int> value{SROOK_NULLOPT};
};

template<>
struct ctoi<'0'>{
	static constexpr SROOK_OPTIONAL<unsigned short int> value = static_cast<unsigned short int>(0u);
};

template<>
struct ctoi<'1'>{
	static constexpr SROOK_OPTIONAL<unsigned short int> value = static_cast<unsigned short int>(1u);
};

template<>
struct ctoi<'2'>{
	static constexpr SROOK_OPTIONAL<unsigned short int> value = static_cast<unsigned short int>(2u);
};

template<>
struct ctoi<'3'>{
	static constexpr SROOK_OPTIONAL<unsigned short int> value = static_cast<unsigned short int>(3u);
};

template<>
struct ctoi<'4'>{
	static constexpr SROOK_OPTIONAL<unsigned short int> value = static_cast<unsigned short int>(4u);
};

template<>
struct ctoi<'5'>{
	static constexpr SROOK_OPTIONAL<unsigned short int> value = static_cast<unsigned short int>(5u);
};

template<>
struct ctoi<'6'>{
	static constexpr SROOK_OPTIONAL<unsigned short int> value = static_cast<unsigned short int>(6u);
};

template<>
struct ctoi<'7'>{
	static constexpr SROOK_OPTIONAL<unsigned short int> value = static_cast<unsigned short int>(7u);
};
template<>
struct ctoi<'8'>{
	static constexpr SROOK_OPTIONAL<unsigned short int> value = static_cast<unsigned short int>(8u);
};

template<>
struct ctoi<'9'>{
	static constexpr SROOK_OPTIONAL<unsigned short int> value = static_cast<unsigned short int>(9u);
};
} // namespace detail

using detail::ctoi;

#ifndef SROOK_CPP_VARIABLE_TEMPLATES
template<char s>
constexpr SROOK_OPTIONAL<unsigned short int> ctoi_v = detail::ctoi<s>::value;
#endif

} // inline namespace mpl
} // inline namespace v1
} // namespace srook

#endif
