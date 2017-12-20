// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_INTRUSIVE_DETAIL_ALGO_TYPE_HPP
#define INCLUDED_SROOK_INTRUSIVE_DETAIL_ALGO_TYPE_HPP

#include <srook/config.hpp>

namespace srook {
namespace intrusive {
SROOK_INLINE_NAMESPACE(v1)

enum algo_types {
    CircularListAlgorithms,
    CircularSListAlgorithms,
    LinearSListAlgorithms,
    CommonSListAlgorithms,
    BsTreeAlgorithms,
    RbTreeAlgorithms,
    AvlTreeAlgorithms,
    SgTreeAlgorithms,
    SplayTreeAlgorithms,
    TreapAlgorithms,
    UnorderedAlgorithms,
    UnorderedCircularSlistAlgorithms,
    AnyAlgorithm
};

template <algo_types, class>
struct get_algo;

template <algo_types, class, class, class>
struct get_node_checker;

SROOK_INLINE_NAMESPACE_END
} // intrusive
} // namespace srook

#endif
