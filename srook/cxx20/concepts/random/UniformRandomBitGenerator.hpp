#ifndef INCLUDED_SROOK_CXX20_CONCEPT_UNIFORMRANDOMBITGENERATOR_HPP
#define INCLUDED_SROOK_CXX20_CONCEPT_UNIFORMRANDOMBITGENERATOR_HPP
#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/is_unsigned.hpp>
#include <srook/type_traits/detail/logical.hpp>

#if SROOK_HAS_CONCEPTS

SROOK_NESTED_NAMESPACE(srook, concepts) {
SROOK_INLINE_NAMESPACE(v1)

template <class G>
SROOK_CONCEPT UniformRandomBitGenerator = 
type_traits::detail::Land<is_integral<SROOK_DEDUCED_TYPENAME G::result_type>, is_unsigned<SROOK_DEDUCED_TYPENAME G::result_type>>::value &&
requires (G g) {
    { G::min() } -> SROOK_DEDUCED_TYPENAME G::result_type;
    { G::max() } -> SROOK_DEDUCED_TYPENAME G::result_type;
    { g() } -> SROOK_DEDUCED_TYPENAME G::result_type;
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(concepts, srook)

#endif
#endif
