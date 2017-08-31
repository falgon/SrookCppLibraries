// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_REMOVE_COPIED_RANGE_ITERATOR_HPP
#define INCLUDED_SROOK_REMOVE_COPIED_RANGE_ITERATOR_HPP
#include <iterator>
#include <srook/config/require.hpp>
#include <srook/iterator/range_iterator.hpp>
#include <srook/iterator/skipping_iterator_value_core.hpp>
#include <srook/type_traits/has_iterator.hpp>

namespace srook {
inline namespace v1 {

namespace {
auto remove_copied_skipper = [](auto &&first, auto &&last, const auto &x) {
    while (x == *first && first != last) ++first;
};
}

template <class Iterator, class T, class Skipper>
struct remove_copied_range_iterator final : skipping_iterator_value_core<Iterator, T, Skipper> {
    using skipping_iterator_value_core<Iterator, T, Skipper>::skipping_iterator_value_core;
};

template <class Iterator, class T>
constexpr remove_copied_range_iterator<std::decay_t<Iterator>, std::decay_t<T>, decltype(remove_copied_skipper)>
make_remove_copied_range_iterator(Iterator &&first, Iterator &&last, T &&t)
{
    return remove_copied_range_iterator<
	std::remove_cv_t<std::decay_t<Iterator>>,
	std::remove_cv_t<std::decay_t<T>>,
	std::remove_cv_t<std::remove_reference_t<decltype(remove_copied_skipper)>>>(std::forward<Iterator>(first), std::forward<Iterator>(last), std::forward<T>(t), std::move(remove_copied_skipper));
}

} // namespace v1
} // namespace srook

#endif
