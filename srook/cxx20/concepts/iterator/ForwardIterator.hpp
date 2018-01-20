#ifndef INCLUDED_SROOK_CXX20_CONCEPTS_ITERATOR_FORWARD_ITERATOR_HPP
#define INCLUDED_SROOK_CXX20_CONCEPTS_ITERATOR_FORWARD_ITERATOR_HPP
#include <srook/cxx20/concepts/iterator/InputIterator.hpp>
#include <srook/cxx20/concepts/iterator/OutputIterator.hpp>
#include <srook/type_traits/is_default_constructible.hpp>
#include <srook/type_traits/add_const.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/is_const.hpp>
#include <srook/type_traits/bool_constant.hpp>

#if SROOK_HAS_CONCEPTS
namespace srook {
namespace concepts {
SROOK_INLINE_NAMESPACE(v1)

template <class Iter>
SROOK_CONCEPT ForwardIterator = srook::concepts::InputIterator<Iter> && requires (Iter i) {
    { i++ } -> Iter;
    { *i++ } -> SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::reference;
} && is_default_constructible<Iter>::value
&& conditional<
    srook::concepts::OutputIterator<Iter>, 
    is_same<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::reference, SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type&>,
    is_same<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::reference, SROOK_DEDUCED_TYPENAME add_const<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type&>::type>
   >::type::value
&& conditional<is_const<Iter>::value, bool_constant<OutputIterator<Iter>>, SROOK_TRUE_TYPE>::type::value;


SROOK_INLINE_NAMESPACE_END

} // namespace concepts
} // namespace srook

#endif
#endif
