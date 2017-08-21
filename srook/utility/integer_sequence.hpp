#ifndef INCLUDED_SROOK_UTILITY_INTEGER_SEQUENCE_HPP
#define INCLUDED_SROOK_UTILITY_INTEGER_SEQUENCE_HPP
#include<cstddef>

namespace srook{

template<class T,T... v>
struct integer_sequence{
	using type = T;
	static constexpr std::size_t size(){return sizeof...(v);}
};

} // namespace srook

#endif
