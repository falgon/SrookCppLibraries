// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANDOM_ALGORITHM_SAMPLE_HPP
#define INCLUDED_SROOK_RANDOM_ALGORITHM_SAMPLE_HPP

#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/cpp_predefined.hpp>
#include <srook/cxx20/concepts/iterator/InputIterator.hpp>
#include <srook/cxx20/concepts/iterator/OutputIterator.hpp>
#include <srook/cxx20/concepts/random/UniformRandomBitGenerator.hpp>
#include <srook/type_traits/iterator.hpp>
#include <srook/type_traits/random/is_uniform_random_bit_generator.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/is_range.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/iterator/range_access.hpp>
#include <srook/algorithm/min.hpp>
#include <cassert>

SROOK_NESTED_NAMESPACE(srook, random, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class PopulationalIterator, class SampleIterator, class Distance, class UniformRandomBitGen>
SROOK_FORCE_INLINE SampleIterator
sample_impl(PopulationalIterator first, PopulationalIterator last, SampleIterator oiter, Distance n, UniformRandomBitGen g, std::input_iterator_tag, std::random_access_iterator_tag)
{
    Distance i = 0;
    for (; first != last && i < n; ++first, ++i) oiter[i] = *first;
    
    for (Distance k = i; first != last; ++first, ++i) {
        Distance r = std::uniform_int_distribution<Distance>(0, i)(g);
        if (r < k) oiter[r] = *first;
    }
    return oiter + srook::algorithm::min(n, i);
}

template <class PopulationalIterator, class SampleIterator, class Distance, class UniformRandomBitGen, class tag>
SROOK_FORCE_INLINE SampleIterator 
sample_impl(PopulationalIterator first, PopulationalIterator last, SampleIterator oiter, Distance n, UniformRandomBitGen&& g, std::forward_iterator_tag, tag)
{
    Distance diff = srook::iterator::distance(first, last);
    for (n = srook::algorithm::min(n, diff); n != 0; ++first) {
        if (std::uniform_int_distribution<Distance>(0, --diff)(g) < n) {
            *oiter++ = *first;
            --n;
        }
    }
    return oiter;
}

} // namespace detail

#if SROOK_HAS_CONCEPTS
template <srook::concepts::InputIterator PopulationalIterator, srook::concepts::OutputIterator SampleIterator, class Distance, srook::concepts::UniformRandomBitGenerator UniformRandomBitGen>
#else
template <class PopulationalIterator, class SampleIterator, class Distance, class UniformRandomBitGen
#   if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
, SROOK_REQUIRES(
    type_traits::detail::Land<
        is_inputiterator<PopulationalIterator>, 
        is_outputiterator<SampleIterator>, 
        is_uniform_random_bit_generator<SROOK_DEDUCED_TYPENAME decay<UniformRandomBitGen>::type>
    >::value
)
#   endif
>
#endif
SROOK_FORCE_INLINE
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        is_integral<Distance>, 
        type_traits::detail::Lor<is_forwarditerator<PopulationalIterator>, is_randomaccessiterator<SampleIterator>>
    >::value,
    SampleIterator
>::type
#else
SampleIterator
#endif
#if SROOK_CPP_RVALUE_REFERENCES
sample(PopulationalIterator first, PopulationalIterator last, SampleIterator oiter, Distance n, UniformRandomBitGen&& g)
#else
sample(PopulationalIterator first, PopulationalIterator last, SampleIterator oiter, Distance n, UniformRandomBitGen& g)
#endif
{
    assert(n >= 0);
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<PopulationalIterator>::difference_type difference_type;
    typedef SROOK_DEDUCED_TYPENAME std::common_type<Distance, difference_type>::type common_t;
    return detail::sample_impl(first, last, oiter, static_cast<common_t>(n), srook::forward<UniformRandomBitGen>(g), 
            SROOK_DEDUCED_TYPENAME std::iterator_traits<PopulationalIterator>::iterator_category(),
            SROOK_DEDUCED_TYPENAME std::iterator_traits<SampleIterator>::iterator_category());
#else
    return detail::sample_impl(first, last, oiter, n, g, 
            SROOK_DEDUCED_TYPENAME std::iterator_traits<PopulationalIterator>::iterator_category(),
            SROOK_DEDUCED_TYPENAME std::iterator_traits<SampleIterator>::iterator_category());
#endif
}

#if SROOK_HAS_CONCEPTS
template <class Range, srook::concepts::OutputIterator SampleIterator, class Distance, srook::concepts::UniformRandomBitGenerator UniformRandomBitGen>
#else
template <class Range, class SampleIterator, class Distance, class UniformRandomBitGen
#   if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
, SROOK_REQUIRES(
    type_traits::detail::Land<
        is_outputiterator<SampleIterator>,
        is_uniform_random_bit_generator<SROOK_DEDUCED_TYPENAME decay<UniformRandomBitGen>::type>
    >::value
)
#   endif
>
#endif
SROOK_FORCE_INLINE
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        is_integral<Distance>,
        is_range<SROOK_DEDUCED_TYPENAME decay<Range>::type>
    >::value,
    SampleIterator
>::type
#else
SampleIterator
#endif
#if SROOK_CPP_RVALUE_REFERENCES
sample(Range&& range, SampleIterator oiter, Distance n, UniformRandomBitGen&& g)
#else
sample(Range& range, SampleIterator oiter, Distance n, UniformRandomBitGen& g)
#endif
{
    assert(n >= 0);
    return
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    sample(srook::begin(range), srook::end(range), oiter, n, srook::forward<UniformRandomBitGen>(g))
#else
    sample(srook::begin(range), srook::end(range), oiter, n, g)
#endif
    ;
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, random, srook)

#endif
