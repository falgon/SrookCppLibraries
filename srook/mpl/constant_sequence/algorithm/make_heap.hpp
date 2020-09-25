// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_MAKE_HEAP_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_MAKE_HEAP_HPP
#include<utility>
#include<type_traits>
#include<srook/mpl/constant_sequence/algorithm/minmax.hpp>
#include<srook/mpl/constant_sequence/algorithm/erase_n.hpp>
#include<srook/mpl/constant_sequence/algorithm/find.hpp>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class>
struct make_heap;

template<std::size_t... seq>
struct make_heap<std::index_sequence<seq...>>{
private:
	static constexpr std::size_t max_value=max_v<std::index_sequence<seq...>>;
public:
	using type=
		concat_t<
			std::index_sequence<max_value>,
			typename make_heap<
				erase_n_t<find_v<max_value,std::index_sequence<seq...>>,std::index_sequence<seq...>>
			>::type
		>;
};

template<>
struct make_heap<std::index_sequence<>>{
	using type=std::index_sequence<>;
};

template<class Seq>
using make_heap_t=typename make_heap<Seq>::type;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
