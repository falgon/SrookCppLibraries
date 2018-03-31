// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_DROP_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_DROP_HPP
#include <srook/config.hpp>
#include <srook/range/adaptor/adaptor_operator.hpp>
#include <srook/iterator/range_iterators/range_iterator.hpp>
#include <srook/iterator/range_access.hpp>

SROOK_NESTED_NAMESPACE(srook, range, adaptors) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

class drop_t {
public:
    SROOK_CONSTEXPR SROOK_FORCE_INLINE drop_t(std::size_t n) SROOK_NOEXCEPT_TRUE 
        : n_(srook::move(n)) {}

    template <class Range, SROOK_REQUIRES(is_range<SROOK_DEDUCED_TYPENAME decay<Range>::type>::value)>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::range::iterator::range_iterator<SROOK_DEDUCED_TYPENAME decay<Range>::type::iterator>
    operator()(Range&& range)
    {
        return srook::range::iterator::make_range_iterator(srook::next(srook::begin(range), n_), srook::end(range));
    }
private:
    std::size_t n_;
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END

SROOK_FORCE_INLINE SROOK_CONSTEXPR detail::drop_t drop(std::size_t n)
SROOK_NOEXCEPT(detail::make_drop_t(n)) { return detail::drop_t(n); }

} SROOK_NESTED_NAMESPACE_END(adaptors, range, srook)
#endif
