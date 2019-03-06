// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONTAINER_DETAIL_LIST_NODE_CORE_HPP
#define INCLUDED_SROOK_CONTAINER_DETAIL_LIST_NODE_CORE_HPP

#include <srook/config.hpp>
#include <srook/type_traits.hpp>
#if 0 && SROOK_HAS_INCLUDE(<compare>)
#   include <compare>
#endif

namespace srook {
namespace container {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <bool> struct comparison {
    template <class L, class R, SROOK_REQUIRES(is_convertible<L, R>::value)>
    static SROOK_CONSTEXPR int apply(const L& l, const R& r) SROOK_NOEXCEPT_TRUE { return !(l == r); }
};

template <> struct comparison<true> {
    template <class L, class R, SROOK_REQUIRES(is_convertible<L, R>::value)>
    static SROOK_CONSTEXPR int apply(const L& l, const R& r) SROOK_NOEXCEPT_TRUE { return l < r ? -1 : l > r ? 1 : 0; }
};

} // namespace detail

template <class T>
struct list_node {
    typedef T value_type;

    T data_;
    list_node* next_ptr;
    list_node* prev_ptr;

#if 0 && SROOK_HAS_INCLUDE(<cmp>)
    template <class U, SROOK_REQUIRES(is_convertible<T, U>::value)>
    SROOK_CONSTEXPR std::common_comparison_category_t<value_type, U> value_compare_3way(const list_node<U>& other) const SROOK_NOEXCEPT_TRUE
    {
        return std::compare_3way(data_, other.data_);
    }
    std::strong_ordering operator<=>(const list_node& other) const SROOK_NOEXCEPT_TRUE
    {
        return next_ptr <=> other.next_ptr != 0 ? next_ptr <=> other.next_ptr : prev_ptr <=> other.prev_ptr;
    }
#else
    template <
        class U, 
        SROOK_REQUIRES(
            type_traits::detail::Land<
                is_convertible<T, U>,
                type_traits::detail::Lor<
                    type_traits::detail::Land<is_equality_comparable<T>, is_equality_comparable<U>>,
                    type_traits::detail::Land<is_less_than_comparable<T>, is_less_than_comparable<U>>
                >
            >::value
        )
    >
    SROOK_CONSTEXPR int value_compare_3way(const list_node<U>& other) const SROOK_NOEXCEPT_TRUE
    {
        SROOK_CONSTEXPR_OR_CONST bool s = type_traits::detail::Land<is_equality_comparable<T>, is_equality_comparable<U>, is_less_than_comparable<T>, is_less_than_comparable<U>>::value;
        return detail::comparison<s>::apply(data_, other.data_);
    }
#endif
};

template <>
struct list_node<void> {
    typedef void value_type;

    list_node* next_ptr;
    list_node* prev_ptr;
#if 0 && SROOK_HAS_INCLUDE(<compare>)
    std::strong_ordering operator<=>(const list_node&) = default;
#endif
};

#if 1 && !SROOK_HAS_INCLUDE(<cmp>)
template <class T>
SROOK_CONSTEXPR bool operator==(const list_node<T>& lhs, const list_node<T>& rhs) SROOK_NOEXCEPT_TRUE
{
    return lhs.next_ptr == rhs.next_ptr && lhs.prev_ptr == rhs.prev_ptr;
}

template <class T>
SROOK_CONSTEXPR bool operator!=(const list_node<T>& lhs, const list_node<T>& rhs) SROOK_NOEXCEPT_TRUE
{
    return !(lhs == rhs);
}
    
template <class T>
SROOK_CONSTEXPR bool operator<(const list_node<T>& lhs, const list_node<T>& rhs) SROOK_NOEXCEPT_TRUE
{
    return lhs.prev_ptr < rhs.prev_ptr && lhs.next_ptr < rhs.next_ptr;    
}
template <class T>
SROOK_CONSTEXPR bool operator>(const list_node<T>& lhs, const list_node<T>& rhs) SROOK_NOEXCEPT_TRUE
{
    return !(lhs < rhs) && lhs != rhs;
}

template <class T>
SROOK_CONSTEXPR bool operator<=(const list_node<T>& lhs, const list_node<T>& rhs) SROOK_NOEXCEPT_TRUE
{
    return (lhs < rhs) || lhs == rhs;
}

template <class T>
SROOK_CONSTEXPR bool operator>=(const list_node<T>& lhs, const list_node<T>& rhs) SROOK_NOEXCEPT_TRUE
{
    return (lhs > rhs) || lhs == rhs;
}
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace container
} // namespace srook

#endif
