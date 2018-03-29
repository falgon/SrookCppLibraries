// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_TRANSFER_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_TRANSFER_HPP
#include <srook/mpl/variadic_player.hpp>
#include <tuple>

namespace srook {
namespace vmpl {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <template <class...> class Range, auto... v>
struct transfer {
    static Range<std::decay_t<decltype(first_v<v...>)>> value;
};
template <template <class...> class Range, auto... v>
Range<std::decay_t<decltype(first_v<v...>)>> transfer<Range, v...>::value{v...};

template <auto... v>
struct transfer<std::tuple, v...> {
    static std::tuple<std::decay_t<decltype(v)>...> value;
};
template <auto... v>
std::tuple<std::decay_t<decltype(v)>...> transfer<std::tuple, v...>::value{v...};

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace vmpl
} // namespace srook

#endif
