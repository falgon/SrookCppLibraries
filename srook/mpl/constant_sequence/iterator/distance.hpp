// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_DISTANCE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_DISTANCE_HPP
#include <cstddef>
#include <srook/config/cpp_predefined/feature_testing.hpp>

namespace srook {
inline namespace mpl {
namespace index_sequence_iterator {
inline namespace v1 {

template <class, class>
struct distance;

template <class Seq1, class Seq2>
struct distance {
private:
    static constexpr bool bigger = Seq1::index < Seq2::index;

public:
    static constexpr std::size_t value = (bigger ? Seq2::index : Seq1::index) - (bigger ? Seq1::index : Seq2::index);
};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class liter, class riter>
constexpr std::size_t distance_v = distance<liter, riter>::value;
#endif

} // namespace v1
} // namespace index_sequence_iterator
} // namespace mpl
} // namespace srook
#endif
