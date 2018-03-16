// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANDOM_ALGORIHTM_SHUFFLE_FISHER_YATES_HPP
#define INCLUDED_SROOK_RANDOM_ALGORIHTM_SHUFFLE_FISHER_YATES_HPP

#include <srook/config.hpp>
#include <srook/iterator/range_access.hpp>
#include <srook/cxx20/concepts/iterator/RandomAccessIterator.hpp>
#include <srook/cxx20/concepts/random/UniformRandomBitGenerator.hpp>
#include <srook/type_traits/iterator/is_randomaccessiterator.hpp>
#include <srook/type_traits/random/is_uniform_random_bit_generator.hpp>
#include <srook/type_traits/make_unsigned.hpp>
#include <srook/type_traits/is_range.hpp>
#include <random>
#include <type_traits>

SROOK_NESTED_NAMESPACE(srook, random, shuffle) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_HAS_CONCEPTS
template <srook::concepts::RandomAccessIterator RandomAccessIter, srook::concepts::UniformRandomBitGenerator UniformRandomNumberGen>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class RandomAccessIter, class UniformRandomNumberGen, 
    SROOK_REQUIRES(type_traits::detail::Land<is_uniform_random_bit_generator<UniformRandomNumberGen>, is_randomaccessiterator<RandomAccessIter>>::value)>
#else
template <class RandomAccessIter, class UniformRandomNumberGen>
#endif
#if SROOK_CPP_RVALUE_REFERENCES
SROOK_FORCE_INLINE void fisher_yates(RandomAccessIter first, RandomAccessIter last, UniformRandomNumberGen&& gen)
#else
SROOK_FORCE_INLINE void fisher_yates(RandomAccessIter first, RandomAccessIter last, UniformRandomNumberGen& gen)
#endif
{
    if (first == last) return;

    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<RandomAccessIter>::difference_type difference_type;
    typedef std::uniform_int_distribution<std::ptrdiff_t> uidp_type;
    typedef SROOK_DEDUCED_TYPENAME uidp_type::param_type param_type;

    difference_type diff = srook::iterator::distance(first, last);
    uidp_type uid;
    for (--last, --diff; first < last; ++first, --diff) std::iter_swap(first, srook::iterator::next(first, uid(gen, param_type(0, diff))));
}

#if SROOK_HAS_CONCEPTS
template <class Range, srook::concepts::UniformRandomBitGenerator UniformRandomNumberGen, SROOK_REQUIRES(is_range<SROOK_DEDUCED_TYPENAME decay<Range>::type>::value)>
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
template <class Range, class UniformRandomNumberGen, 
    SROOK_REQUIRES(type_traits::detail::Land<is_range<SROOK_DEDUCED_TYPENAME decay<Range>::type>, is_uniform_random_bit_generator<SROOK_DEDUCED_TYPENAME decay<UniformRandomNumberGen>::type>>::value)>
#else
template <class Range, class UniformRandomNumberGen>
#endif
#if SROOK_CPP_RVALUE_REFERENCES
SROOK_FORCE_INLINE void fisher_yates(Range&& range, UniformRandomNumberGen&& gen)
#else
SROOK_FORCE_INLINE void fisher_yates(Range& range, UniformRandomNumberGen& gen)
#endif
{
    srook::random::shuffle::fisher_yates(srook::begin(range), srook::end(range), srook::forward<UniformRandomNumberGen>(gen));
}


SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(shuffle, random, srook)

#endif
