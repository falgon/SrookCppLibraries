// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_EMPLACE_BACK_HPP
#define INCLUDED_EMPLACE_BACK_HPP

namespace srook {
inline namespace v1 {
template <class Container, class... Args>
inline void emplace_back(Container &container, Args &&... args)
{
    container.emplace_back(args...);
}

template <class Container, class Add_Element>
inline void push_back(Container &container, Add_Element &&args)
{
    container.push_back(args);
}
} // namespace v1
} // namespace srook

#endif
