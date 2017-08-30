// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ITERATOR_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ITERATOR_HPP
#include <srook/mpl/constant_sequence/algorithm/at.hpp>
#include <type_traits>
#include <utility>

namespace srook {
inline namespace mpl {
namespace index_sequence_iterator {
inline namespace v1 {

template <class>
struct index_sequence_iterator;

template <std::size_t head, std::size_t... tail>
struct index_sequence_iterator<std::index_sequence<head, tail...>> {
    static constexpr std::size_t value = head;
    static constexpr std::size_t index = 0;
    using type = std::index_sequence<head, tail...>;
};

template <class>
struct increment;
template <class>
struct decrement;

template <class Seq>
struct increment<index_sequence_iterator<Seq>> {
    static constexpr std::size_t index = index_sequence_iterator<Seq>::index + 1;
    static constexpr std::size_t value = constant_sequence::at_v<index, Seq>;
    using type = Seq;
};

template <class Seq>
struct increment<increment<Seq>> {
    static constexpr std::size_t index = increment<Seq>::index + 1;
    static constexpr std::size_t value = constant_sequence::at_v<index, typename increment<Seq>::type>;
    using type = typename increment<Seq>::type;
};

template <class Seq>
struct increment<decrement<Seq>> {
    static constexpr std::size_t index = decrement<Seq>::index + 1;
    static constexpr std::size_t value = constant_sequence::at_v<index, typename decrement<Seq>::type>;
    using type = typename increment<Seq>::type;
};

template <class Seq>
struct decrement<index_sequence_iterator<Seq>> {
    static constexpr std::size_t index = index_sequence_iterator<Seq>::index - 1;
    static constexpr std::size_t value = constant_sequence::at_v<index, Seq>;
    using type = Seq;
};

template <class Seq>
struct decrement<decrement<Seq>> {
    static constexpr std::size_t index = decrement<Seq>::index - 1;
    static constexpr std::size_t value = constant_sequence::at_v<index, typename decrement<Seq>::type>;
    using type = typename decrement<Seq>::type;
};

template <class Seq>
struct decrement<increment<Seq>> {
    static constexpr std::size_t index = increment<Seq>::index - 1;
    static constexpr std::size_t value = constant_sequence::at_v<index, typename increment<Seq>::type>;
    using type = typename decrement<Seq>::type;
};

} // namespace v1
} // namespace index_sequence_iterator
} // namespace mpl
} // namespace srook

#endif
