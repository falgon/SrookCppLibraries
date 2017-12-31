// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INLCUDED_SROOK_INTRUSIVE_DETAIL_COMMON_SLIST_ALGORITHMS_HPP
#define INLCUDED_SROOK_INTRUSIVE_DETAIL_COMMON_SLIST_ALGORITHMS_HPP

#include <srook/intrusive/detail/config_begin.hpp>
#ifdef _MSC_VER
#   pragma once
#endif
#include <cstddef>
#include <cassert>
#include <srook/intrusive/detail/algo_type.hpp>

namespace srook {
namespace intrusive {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class NodeTraits>
class common_slist_algorithms {
public:
    typedef SROOK_DEDUCED_TYPENAME NodeTraits::node_type node_type;
    typedef SROOK_DEDUCED_TYPENAME NodeTraits::node_pointer node_pointer;
    typedef SROOK_DEDUCED_TYPENAME NodeTraits::const_node_pointer const_node_pointer;
    typedef NodeTraits node_traits;

    static node_pointer get_previous_node(node_pointer p, const node_pointer& this_node)
    {
        for(node_pointer p_next; this_node != (p_next = node_traits::get_next(p)); p = p_next) {
            assert((p && SROOK_CURRENT_FUNCTION));
        }
        return p;
    }

    SROOK_FORCE_INLINE static void init(const node_pointer& this_node)
    {
        node_traits::set_next(this_node, node_pointer());
    }

    SROOK_FORCE_INLINE static bool unique(const const_node_pointer& this_node)
    {
        node_pointer next = node_traits::get_next(this_node);
        return !next || next == this_node;
    }

    SROOK_FORCE_INLINE static bool inited(const const_node_pointer& this_node)
    {
        return !node_traits::get_next(this_node);
    }

    SROOK_FORCE_INLINE static void unlink_after(const node_pointer& prev_node)
    {
        const_node_pointer this_node(node_traits::get_next(prev_node));
        node_traits::set_next(prev_node, node_traits::get_next(this_node));
    }

    SROOK_FORCE_INLINE static void unlink_after(const node_pointer& prev_node, const node_pointer& last_node)
    {
        node_traits::set_next(prev_node, last_node);
    }

    SROOK_FORCE_INLINE static void link_after(const node_pointer& prev_node, const node_pointer& this_node)
    {
        node_traits::set_next(this_node, node_traits::get_next(prev_node));
        node_traits::set_next(prev_node, this_node);
    }

    SROOK_FORCE_INLINE static void incorporate_after(const node_pointer& bp, const node_pointer& b, const node_pointer& be)
    {
        node_pointer p(node_traits::get_next(bp));
        node_traits::set_next(bp, b);
        node_traits::set_next(be, p);
    }

    static void transfer_after(const node_pointer& bp, const node_pointer& bb, const node_pointer& be)
    {
        if (bp != bb && bp != be && bb != be) {
            node_pointer next_b = node_traits::get_next(bb);
            node_pointer next_e = node_traits::get_next(be);
            node_pointer next_p = node_traits::get_next(bp);
            node_traits::set_next(bb, next_e);
            node_traits::set_next(be, next_p);
            node_traits::set_next(bp, next_b);
        }
    }

    struct stable_partition_info {
        std::size_t num_1st_partition;
        std::size_t num_2nd_partition;
        node_pointer beg_2st_partition;
        node_pointer new_last_node;
    };

    template <class Pred>
    static void stable_partition(node_pointer before_beg, const node_pointer& end, Pred pred, stable_partition_info& info)
    {
        node_pointer bcur = before_beg;
        node_pointer cur = node_traits::get_next(bcur);
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
                            last_to_remove = cur;
                            node_pointer next = node_traits::get_next(cur);
                            node_traits::set_next(bcur, next);
                            cur = next;
                        } else {
                            ++n2;
                            bcur = cur;
                            cur = node_traits::get_next(cur);
                        }
                    }
                } SROOK_CATCH(...) {
                    node_traits::set_next(last_to_remove, new_f);
                    SROOK_THROW;
                }
                node_traits::set_next(last_to_remove, new_f);
                break;
            }
        }
        info.num_1st_partition = n1;
        info.num_2nd_partition = n2;
        info.beg_2st_partition = new_f;
        info.new_last_node = bcur;
    }

    static std::size_t distance(const const_node_pointer& f, const const_node_pointer& l)
    {
        const_node_pointer i(f);
        std::size_t res = 0;

        for(; i != l; ++res) {
            i = node_traits::get_next(i);
        }
        return res;
    }
};

} // namespace detail

template <class NodeTraits>
struct get_algo<CommonSListAlgorithms, NodeTraits> {
    typedef detail::common_slist_algorithms<NodeTraits> type;
};

SROOK_INLINE_NAMESPACE_END
} // namespace intrusive
} // namespace srook

#include <srook/intrusive/detail/config_end.hpp>
#endif
