#ifndef INCLUDED_SROOK_CXX20_CONCEPT_RANDOM_SEEDSEQUENCE_HPP
#define INCLUDED_SROOK_CXX20_CONCEPT_RANDOM_SEEDSEQUENCE_HPP
#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/is_unsigned.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/cstdint.hpp>
#include <vector> // for InputIterator, RandomAccessIterator, OutputIterator
#include <initializer_list>

#if SROOK_HAS_CONCEPTS

SROOK_NESTED_NAMESPACE(srook, concepts) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

typedef std::vector<srook::uint_least32_t>::iterator uileast32_iter;
typedef uileast32_iter mutable_raiter;
typedef uileast32_iter output_iter;

} // namespace detail

template <class S>
SROOK_CONCEPT SeedSequence = 
type_traits::detail::Land<
    is_integral<SROOK_DEDUCED_TYPENAME S::result_type>, 
    is_unsigned<SROOK_DEDUCED_TYPENAME S::result_type>, 
    bool_constant<sizeof(SROOK_DEDUCED_TYPENAME S::result_type) >= 4>
>::value &&
requires (S q, const S r) {
    S();
    S(detail::uileast32_iter(), detail::uileast32_iter());
    S(std::initializer_list<SROOK_DEDUCED_TYPENAME S::result_type>());
    { q.generate(detail::mutable_raiter(), detail::mutable_raiter()) } -> void;
    { r.size() } -> std::size_t;
    { r.param(detail::output_iter()) } -> void;
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(concepts, srook)

#endif
#endif
