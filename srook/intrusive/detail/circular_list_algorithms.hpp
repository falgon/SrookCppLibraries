// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_INTRUSIVE_CIRCULAR_LIST_ALGORITHMS_HPP
#define INCLUDED_SROOK_INTRUSIVE_CIRCULAR_LIST_ALGORITHMS_HPP

#include <srook/intrusive/detail/config_begin.hpp>
#include <srook/intrusive/detail/algo_type.hpp>
#include <cstddef>

#ifdef _MSC_VER
#   pragma once
#endif

namespace srook {
namespace intrusive {
SROOK_INLINE_NAMESPACE(v1)

template <class NodeTraits>
class circular_list_algorithms {
public:
    typedef SROOK_DEDUCED_TYPENAME NodeTraits::node_type node_type;
    typedef SROOK_DEDUCED_TYPENAME NodeTraits::node_pointer node_pointer;
    typedef SROOK_DEDUCED_TYPENAME NodeTraits::const_node_pointer const_node_pointer;
    typedef NodeTraits node_traits;

    SROOK_FORCE_INLINE static void init(const node_pointer& this_node)
    {
        const node_pointer null_node();
        node_traits::set_next(this_node, null_node);
        node_traits::set_previous(this_node, null_node);
    }

    SROOK_FORCE_INLINE static bool inited(const const_node_pointer& this_node)
    {
        return !node_traits::get_next(this_node);
    }

    SROOK_FORCE_INLINE static void init_header(const node_pointer& this_node)
    {
        node_traits::set_next(this_node, this_node);
        node_traits::set_previous(this_node, this_node);
    }

    SROOK_FORCE_INLINE static bool unique(const const_node_pointer& this_node)
    {
        node_pointer next = node_traits::get_next(this_node);
        return !next || next == this_node;
    }

    static std::size_t count(const const_node_pointer& this_node)
    {
        std::size_t res = 0;
        const_node_pointer p = this_node;
        do {
            p = node_traits::get_next(p);
            ++res;
        } while (p != this_node);
        return res;
    }

    SROOK_FORCE_INLINE static node_pointer unlink(const node_pointer& this_node)
    {
        node_pointer next(node_traits::get_next(this_node));
        node_pointer prev(node_traits::get_previous(this_node));
        node_traits::set_next(prev, next);
        node_traits::set_previous(next, prev);
        return next;
    }

    SROOK_FORCE_INLINE static void unlink(const node_pointer& b, const node_pointer& e)
    {
        if (b != e) {
            node_pointer prevb(node_traits::get_previous(b));
            node_traits::set_previous(e, prevb);
            node_traits::set_next(prevb, e);
        }
    }

    SROOK_FORCE_INLINE static void link_before(const node_pointer& next_node, const node_pointer& this_node)
    {
        node_pointer prev(node_traits::get_previous(next_node));
        node_traits::set_previous(this_node, prev);
        node_traits::set_next(this_node, next_node);
        node_traits::set_previous(next_node, this_node);
        node_traits::set_next(prev, this_node);
    }

    SROOK_FORCE_INLINE static void link_after(const node_pointer& prev_node, const node_pointer& this_node)
    {
        node_pointer next(node_traits::get_next(prev_node));
        node_traits::set_previous(this_node, prev_node);
        node_traits::set_next(this_node, next);
        node_traits::set_next(prev_node, this_node);
        node_traits::set_previous(next, this_node);
    }

    static void swap_nodes(const node_pointer& this_node, const node_pointer& other_node)
    {
        if (other_node == this_node) return;
        if (inited(this_node)) init_header(this_node);
        if (inited(other_node)) init_header(other_node);

        node_pointer next_this(node_traits::get_next(this_node));
        node_pointer prev_this(node_traits::get_previous(this_node));
        node_pointer next_other(node_traits::get_next(other_node));
        node_pointer prev_other(node_traits::get_previous(other_node));

        swap_prev(next_this, next_other);
        swap_next(prev_this, prev_other);
        swap_next(this_node, other_node);
        swap_prev(this_node, other_node);

        if (inited(this_node)) init(other_node);
        if (inited(other_node)) init(this_node);
    }

    static void transfer(const node_pointer& p, const node_pointer& b, const node_pointer& e)
    {
        if (b == e) return;

        node_pointer prev_p(node_traits::get_previous(p));
        node_pointer prev_b(node_traits::get_previous(b));
        node_pointer prev_e(node_traits::get_previous(e));

        node_traits::set_next(prev_e, p);
        node_traits::set_previous(p, prev_e);
        node_traits::set_next(prev_b, e);
        node_traits::set_previous(e, prev_b);
        node_traits::set_next(prev_p, b);
        node_traits::set_previous(b, prev_p);
    }

    static void transfer(const node_pointer& p, const node_pointer& i)
    {
        node_pointer n(node_traits::get_next(i));
        if (n != p && i != p) {
            node_pointer prev_p(node_traits::get_previous(p));
            node_pointer prev_i(node_traits::get_previous(i));
            node_traits::set_next(prev_p, i);
            node_traits::set_previous(i, prev_p);
            node_traits::set_next(i, p);
            node_traits::set_previous(p, i);
            node_traits::set_previous(n, prev_i);
            node_traits::set_next(prev_i, n);
        }
    }

    static void reverse(const node_pointer& p)
    {
        node_pointer f(node_traits::get_next(p));
        node_pointer i(node_traits::get_next(f)), e(p);
     
        while (i != e) {
            node_pointer n = i;
            i = node_traits::get_next(i);
            transfer(f, n, i);
            f = n;
        }
    }

    static void move_backwards(const node_pointer& p, std::size_t n)
    {
        if (!n) return;

        node_pointer first = node_traits::get_next(p);
        if (first == node_traits::get_previous(p)) return;
        
        unlink(p);
        while (n--) {
            first = node_traits::get_next(first);
        }
        link_before(first, p);
    }

    static void move_forward(const node_pointer& p, std::size_t n)
    {
        if (!n) return;

        node_pointer last = node_traits::get_previous(p);
        if (last == node_traits::get_next(p)) return;

        unlink(p);
        while (n--) {
            last = node_traits::get_previous(last);
        }
        link_after(last, p);
    }

    static std::size_t distance(const const_node_pointer& f, const const_node_pointer& l)
    {
        const_node_pointer i(f);
        std::size_t res = 0;
        
        for(; i != l; ++res) i = node_traits::get_next(i);    
        return res;
    }

    struct stable_partition_info {
        std::size_t num_1st_partition;
        std::size_t num_2nd_partition;
        node_pointer beg_2st_partition;
    };

    template <class Pred>
    static void stable_partition(node_pointer beg, const node_pointer& end, Pred pred, stable_partition_info& info)
    {
        node_pointer bcur = node_traits::get_previous(beg);
        node_pointer cur = beg;
        node_pointer new_f = end;

        std::size_t n1 = 0, n2 = 0;
        
        while (cur != end) {
            if (pred(cur)) {
               ++n1;
               bcur = cur;
               cur = node_traits::get_next(cur);
            } else {
                ++n2;
                node_pointer last_to_remove = bcur;
                new_f = cur;
                bcur = cur;
                cur = node_traits::get_next(cur);

                SROOK_TRY {
                    while (cur != end) {
                        if (pred(cur)) {
                            ++n1;
                            node_traits::set_next(last_to_remove, cur);
                            node_traits::set_previous(cur, last_to_remove);
                            last_to_remove = cur;
                            node_pointer next = node_traits::get_next(cur);
                            node_traits::set_next(bcur, next);
                            node_traits::set_previous(next, bcur);
                            cur = next;
                        } else {
                            ++n2;
                            bcur = cur;
                            cur = node_traits::get_next(cur);
                        }
                    }
                } SROOK_CATCH (...) {
                    node_traits::set_next(last_to_remove, new_f);
                    node_traits::set_previous(new_f, last_to_remove);
                    SROOK_THROW;
                }
                node_traits::set_next(last_to_remove, new_f);
                node_traits::set_previous(new_f, last_to_remove);
                break;
            }
        }
        info.num_1st_partition = n1;
        info.num_2nd_partition = n2;
        info.beg_2st_partition = new_f;
    }
private:
    SROOK_FORCE_INLINE static void swap_prev(const node_pointer& this_node, const node_pointer& other_node)
    {
        node_pointer t(node_traits::get_previous(this_node));
        node_traits::set_previous(this_node, node_traits::get_previous(other_node));
        node_traits::set_previous(other_node, t);
    }

    SROOK_FORCE_INLINE static void swap_next(const node_pointer& this_node, const node_pointer& other_node)
    {
        node_pointer t(node_traits::get_next(this_node));
        node_traits::set_next(this_node, node_traits::get_next(other_node));
        node_traits::set_next(other_node, t);
    }
};

template <class NodeTraits>
struct get_algo<CircularListAlgorithms, NodeTraits> {
    typedef circular_list_algorithms<NodeTraits> type;
};

SROOK_INLINE_NAMESPACE_END
} // namespace intrusive
} // namespace srook

#include <srook/intrusive/detail/config_end.hpp>
#endif
