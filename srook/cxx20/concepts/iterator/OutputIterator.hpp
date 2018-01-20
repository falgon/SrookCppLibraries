#ifndef INCLUDED_SROOK_CXX20_CONCEPTS_ITERATOR_OUTPUT_ITERATOR_HPP
#define INCLUDED_SROOK_CXX20_CONCEPTS_ITERATOR_OUTPUT_ITERATOR_HPP
#include <srook/cxx20/concepts/iterator/Iterator.hpp>
#include <srook/type_traits/is_class.hpp>
#include <srook/type_traits/is_pointer.hpp>
#include <srook/type_traits/is_convertible.hpp>
#include <srook/type_traits/remove_pointer.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/utility/void_t.hpp>
#if SROOK_HAS_CONCEPTS
namespace srook {
namespace concepts {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class P, class = SROOK_DEDUCED_TYPENAME voider<>::type>
struct iter_pointer_value_type 
    : public type_constant<SROOK_DEDUCED_TYPENAME remove_pointer<P>::value_type> {};

template <class Iter>
struct iter_pointer_value_type<Iter, SROOK_DEDUCED_TYPENAME voider<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type>::type>
    : public type_constant<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type> {};

} // namespace detail

template <class Iter>
SROOK_CONCEPT OutputIterator = srook::concepts::Iterator<Iter> || type_traits::detail::Lor<is_class<Iter>, is_pointer<Iter>>::value
&& requires (Iter r, SROOK_DEDUCED_TYPENAME detail::iter_pointer_value_type<Iter>::type o) {
    *r = o;
    *r++ = o;
    { ++r } -> Iter&;
    { r++ } -> Iter&;
    { *r++ } -> const Iter&;
};

SROOK_INLINE_NAMESPACE_END
} // namespace concepts
} // namespace srook

#endif
#endif
