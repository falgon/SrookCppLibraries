#ifndef INCLUDED_SROOK_ITERATOR_ITERATOR_TRAITS_HPP
#define INCLUDED_SROOK_ITERATOR_ITERATOR_TRAITS_HPP

#include <iterator>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <srook/type_traits/is_pointer.hpp>
#include <srook/type_traits/detail/logical.hpp>

SROOK_NESTED_NAMESPACE(srook, iterator) {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct iterator_traits : public std::iterator_traits<T> {
 //   SROOK_STATIC_ASSERT((type_traits::detail::Lor<is_pointer<T>, is_iterator<T>>::value), "Type must be iterator or pointer");
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, srook)

namespace srook {

using srook::iterator::iterator_traits;

} // namespace srook

#endif
