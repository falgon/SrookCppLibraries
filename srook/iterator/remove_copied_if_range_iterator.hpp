// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_ITERATOR_REMOVE_COPIED_IF_HPP
#define INCLUDED_SROOK_ITERATOR_REMOVE_COPIED_IF_HPP
#include <iterator>
#include <srook/config/require.hpp>
#include <srook/iterator/range_iterator.hpp>
#include <srook/iterator/skipping_iterator_functor_core.hpp>
#include <srook/type_traits/has_iterator.hpp>
#include <srook/type_traits/is_callable.hpp>

namespace srook {
inline namespace v1 {

namespace {
const auto remove_copied_if_skipper = [](auto &&first, auto &&last, const auto &pred) {
    while (pred(*first) && first != last) ++first;
};
}

template <class Iterator, class Predicate, class Skipper>
struct remove_copied_if_range_iterator : skipping_iterator_functor_core<Iterator, Predicate, Skipper> {
    using skipping_iterator_functor_core<Iterator, Predicate, Skipper>::skipping_iterator_functor_core;
};

template <class Iterator, class T>
constexpr remove_copied_if_range_iterator<
    std::remove_cv_t<std::decay_t<Iterator>>,
    std::remove_cv_t<std::decay_t<T>>,
    std::remove_cv_t<decltype(remove_copied_if_skipper)>>
make_remove_copied_if_range_iterator(Iterator &&first, Iterator &&last, T &&t)
{
    return remove_copied_if_range_iterator<
	std::remove_cv_t<std::decay_t<Iterator>>,
	std::remove_cv_t<std::decay_t<T>>,
	std::remove_cv_t<decltype(remove_copied_if_skipper)>>(std::forward<Iterator>(first), std::forward<Iterator>(last), std::forward<T>(t), std::move(remove_copied_if_skipper));
}

} // namespace v1
} // namespace srook

#endif
