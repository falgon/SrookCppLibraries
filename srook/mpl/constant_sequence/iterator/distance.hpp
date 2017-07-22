// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_DISTANCE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_DISTANCE_HPP
#include<cstddef>
namespace srook{
inline namespace mpl{
namespace index_sequence_iterator{
inline namespace v1{

template<class,class>
struct distance;

template<class Seq1,class Seq2>
struct distance{
private:
	static constexpr bool bigger=Seq1::index<Seq2::index;
public:
	static constexpr std::size_t value=(bigger?Seq2::index:Seq1::index)-(bigger?Seq1::index:Seq2::index);
};

template<class liter,class riter>
constexpr std::size_t distance_v=distance<liter,riter>::value;

} // inline namespace v1
} // namespace index_sequence_iterator 
} // inline namespace mpl 
} // namespace srook
#endif
