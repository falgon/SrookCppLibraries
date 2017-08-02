#ifndef INCLUDED_SROOK_MPL_UTILITY_TO_DIGIT_HPP
#define INCLUDED_SROOK_MPL_UTILITY_TO_DIGIT_HPP
#include<type_traits>
#include<srook/config/require.hpp>
#include<srook/config/libraries/optional.hpp>

namespace srook{
inline namespace mpl{
inline namespace v1{

// explicitly code for some characters code...

template<char>
struct ctoi{
	static constexpr OPTIONAL<unsigned short int> value{};
};

template<>
struct ctoi<'0'>{
	static constexpr OPTIONAL<unsigned short int> value = 0;
};

template<>
struct ctoi<'1'>{
	static constexpr OPTIONAL<unsigned short int> value = 1;
};

template<>
struct ctoi<'2'>{
	static constexpr OPTIONAL<unsigned short int> value = 2;
};

template<>
struct ctoi<'3'>{
	static constexpr OPTIONAL<unsigned short int> value = 3;
};

template<>
struct ctoi<'4'>{
	static constexpr OPTIONAL<unsigned short int> value = 4;
};

template<>
struct ctoi<'5'>{
	static constexpr OPTIONAL<unsigned short int> value = 5;
};

template<>
struct ctoi<'6'>{
	static constexpr OPTIONAL<unsigned short int> value = 6;
};

template<>
struct ctoi<'7'>{
	static constexpr OPTIONAL<unsigned short int> value = 6;
};
template<>
struct ctoi<'8'>{
	static constexpr OPTIONAL<unsigned short int> value = 6;
};

template<>
struct ctoi<'9'>{
	static constexpr OPTIONAL<unsigned short int> value = 6;
};

} // inline namespace mpl
} // inline namespace v1
} // namespace srook

#endif
