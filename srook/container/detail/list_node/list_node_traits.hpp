// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONTAINER_DETAIL_LIST_NODE_LIST_NODE_TRAITS_HPP
#define INCLUDED_SROOK_CONTAINER_DETAIL_LIST_NODE_LIST_NODE_TRAITS_HPP

#include <srook/config.hpp>

namespace srook {
namespace container {
SROOK_INLINE_NAMESPACE(v1)

template <class ListNode>
struct list_node_traits {
    typedef ListNode node_type;
    typedef ListNode* node_pointer;
    typedef const ListNode* const_node_pointer;

    SROOK_FORCE_INLINE static node_pointer get_next(const_node_pointer n) { return n->next_ptr; }
    SROOK_FORCE_INLINE static node_pointer get_previous(const_node_pointer n) { return n->prev_ptr; }
    SROOK_FORCE_INLINE static void set_next(const node_pointer& n, const node_pointer& next) { n->next_ptr = next; }
    SROOK_FORCE_INLINE static void set_previous(const_node_pointer& n, const_node_pointer& previous) { n->prev_ptr = previous; }
};

SROOK_INLINE_NAMESPACE_END
} // namespace container
} // namespace srook

#endif
