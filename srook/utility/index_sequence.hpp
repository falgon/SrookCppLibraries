#ifndef INCLUDED_SROOK_UTILITY_INDEX_SEQUENCE_HPP
#define INCLUDED_SROOK_UTILITY_INDEX_SEQUENCE_HPP
#include<srook/type_traits/integer_sequence.hpp>

namespace srook{

template<std::size_t... v>
struct index_sequence{
	using type = std::size_t;
	static constexpr std::size_t size(){return sizeof...(v);}
};


} // namespace srook

#endif
