// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_MAKE_INDEX_SEQUENCE_ITERATOR_RANGE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_MAKE_INDEX_SEQUENCE_ITERATOR_RANGE_HPP
#include <srook/mpl/constant_sequence/algorithm/concat.hpp>
#include <srook/mpl/constant_sequence/algorithm/first.hpp>
#include <srook/mpl/constant_sequence/algorithm/partial_head.hpp>
#include <srook/mpl/constant_sequence/algorithm/partial_tail.hpp>
#include <srook/mpl/constant_sequence/algorithm/pop_back.hpp>
#include <srook/mpl/constant_sequence/algorithm/pop_front.hpp>
#include <srook/mpl/constant_sequence/iterator/index_sequence_iterator.hpp>
#include <type_traits>

namespace srook {
inline namespace mpl {
namespace index_sequence_iterator {
inline namespace v1 {

template <class, class>
struct make_index_sequence_iterator_range;

template <class Seq1, class Seq2>
struct make_index_sequence_iterator_range {
private:
    static_assert(std::is_same_v<typename Seq1::type, typename Seq2::type>);
    using range_type = typename Seq1::type;

    template <class, std::size_t>
    struct ignore_sequence;
    template <std::size_t... seq, std::size_t pop_count>
    struct ignore_sequence<std::index_sequence<seq...>, pop_count> {
	using type = typename ignore_sequence<constant_sequence::pop_back_t<std::index_sequence<seq...>>, pop_count - 1>::type;
    };
    template <std::size_t... seq>
    struct ignore_sequence<std::index_sequence<seq...>, 0> {
	using type = std::index_sequence<seq...>;
    };
    template <class Seq, std::size_t counter>
    using ignore_sequence_t = typename ignore_sequence<Seq, counter>::type;

public:
    using type =
	constant_sequence::concat_t<
	    std::index_sequence<constant_sequence::first_v<constant_sequence::partial_tail_t<Seq1::index, range_type>>>,
	    constant_sequence::partial_tail_t<
		(Seq2::index - Seq1::index == 1) ? 2 : (Seq2::index - Seq1::index) % 2 == 0 ? Seq2::index - Seq1::index : Seq2::index - Seq1::index - 1,
		ignore_sequence_t<
		    range_type,
		    (Seq2::type::size() - Seq2::index - 1)>>>;
};

template <class Seq1, class Seq2>
using make_index_sequence_iterator_range_t = typename make_index_sequence_iterator_range<Seq1, Seq2>::type;

} // namespace v1
} // namespace index_sequence_iterator
} // namespace mpl
} // namespace srook
#endif
