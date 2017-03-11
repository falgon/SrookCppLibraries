#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_MERGE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_MERGE_HPP
#include<srook/mpl/constant_sequence/algorithm/sort.hpp>
#include<srook/mpl/constant_sequence/algorithm/first.hpp>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<bool,class,class,template<std::size_t,std::size_t>class>
struct merge;

template<
	std::size_t head1,std::size_t head_next1,std::size_t... tail1,
	std::size_t head2,std::size_t... tail2,
	template<std::size_t,std::size_t>class comp
>
struct merge<true,std::index_sequence<head1,head_next1,tail1...>,std::index_sequence<head2,tail2...>,comp>{
	using type=
		concat_t<
			std::index_sequence<head1>,
			typename merge<
				comp<head_next1,head2>::value,
				std::index_sequence<head_next1,tail1...>,
				std::index_sequence<head2,tail2...>,
				comp
			>::type
		>;
};

template<
	std::size_t head1,std::size_t... tail1,
	std::size_t head2,std::size_t head_next2,std::size_t... tail2,
	template<std::size_t,std::size_t>class comp
>
struct merge<false,std::index_sequence<head1,tail1...>,std::index_sequence<head2,head_next2,tail2...>,comp>{
	using type=
		concat_t<
			std::index_sequence<head2>,
			typename merge<
				comp<head1,head_next2>::value,
				std::index_sequence<head1,tail1...>,
				std::index_sequence<head_next2,tail2...>,
				comp
			>::type
		>;	
};

template<
	std::size_t last1,
	std::size_t prev_last,std::size_t... last2,
	template<std::size_t,std::size_t>class comp
>
struct merge<true,std::index_sequence<last1>,std::index_sequence<prev_last,last2...>,comp>{
	using type=std::index_sequence<last1,prev_last,last2...>;
};

template<
	std::size_t last1,
	std::size_t prev_last,std::size_t prev_next_last2,std::size_t... last2,
	template<std::size_t,std::size_t>class comp
>
struct merge<false,std::index_sequence<last1>,std::index_sequence<prev_last,prev_next_last2,last2...>,comp>{
	using type=
		concat_t<
			std::index_sequence<prev_last>,
			typename merge<
				comp<last1,prev_next_last2>::value,
				std::index_sequence<last1>,
				std::index_sequence<prev_next_last2,last2...>,
				comp
			>::type
		>;
};

/*template<std::size_t last1,std::size_t last2,template<std::size_t,std::size_t>class comp>
struct merge<true,std::index_sequence<last1>,std::index_sequence<last2>,comp>{
	using type=std::index_sequence<last1,last2>;
};

template<std::size_t last1,std::size_t last2,template<std::size_t,std::size_t>class comp>
struct merge<false,std::index_sequence<last1>,std::index_sequence<last2>,comp>{
	using type=std::index_sequence<last2,last1>;
};*/

template<bool b,std::size_t last,template<std::size_t,std::size_t>class comp>
struct merge<b,std::index_sequence<last>,std::index_sequence<>,comp>{
	using type=std::index_sequence<last>;
};

template<std::size_t prev_last,std::size_t next_last,std::size_t... last1,std::size_t last2,template<std::size_t,std::size_t>class comp>
struct merge<true,std::index_sequence<prev_last,next_last,last1...>,std::index_sequence<last2>,comp>{
	using type=
		concat_t<
			std::index_sequence<prev_last>,
			typename merge<
				comp<next_last,last2>::value,
				std::index_sequence<next_last,last1...>,
				std::index_sequence<last2>,
				comp
			>::type
		>;
};

template<std::size_t... last1,std::size_t last2,template<std::size_t,std::size_t>class comp>
struct merge<false,std::index_sequence<last1...>,std::index_sequence<last2>,comp>{
	using type=std::index_sequence<last2,last1...>;
};



template<class Seq1,class Seq2,template<std::size_t,std::size_t>class comp=less>
using merge_t=
	typename merge<
		(Seq1::size()<Seq2::size())?comp<first_v<Seq1>,first_v<Seq2>>::value:comp<first_v<Seq2>,first_v<Seq1>>::value,
		std::conditional_t<(Seq1::size()<Seq2::size()),Seq1,Seq2>,
		std::conditional_t<(Seq1::size()<Seq2::size()),Seq2,Seq1>,
		comp
	>::type;

} // inline namespace v1
} // inline namespace constant_sequence
} // inline namespace mpl 
} // namespace srook
#endif
