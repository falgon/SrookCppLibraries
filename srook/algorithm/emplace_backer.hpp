// Copyright (C) 2017 roki
#ifndef INCLUDED_EMPLACE_BACKER_HPP
#define INCLUDED_EMPLACE_BACKER_HPP
#include <utility>

namespace srook {
inline namespace v1 {

template <class Container, class... Args>
constexpr void emplace_backer(Container &&v, Args &&... args)
{
    (v.emplace_back(std::forward<Args>(args)), ...);
}
template <class Container, class... Args>
constexpr void push_backer(Container &&v, Args &&... args)
{
    (v.push_back(std::forward<Args>(args)), ...);
}

} // namespace v1
} // namespace srook

#endif
