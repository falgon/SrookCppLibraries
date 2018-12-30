// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MUTEX_GENERIC_DETAIL_TRY_LOCKER_HPP
#define INCLUDED_SROOK_MUTEX_GENERIC_DETAIL_TRY_LOCKER_HPP
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPP_VARIADIC_TEMPLATES && (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
#    include <srook/config/feature/inline_namespace.hpp>
#    include <srook/mpl/variadic_player.hpp>
#    include <srook/mutex/guards/unique_lock.hpp>

namespace srook {
namespace cxx11 {
namespace mutexes {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <int I, bool Continue>
struct try_locker {
    template <class... Lock>
    static void do_try_lock(const std::tuple<Lock&...>& locks, int& index)
    {
        index = I;
        unique_lock<typename variadic_types::detail::At<I, Lock...>::type> l(std::get<I>(locks), try_to_lock);

        if (l.owns_lock()) {
            try_locker<I + 1, (I + 2 < sizeof...(Lock))>::do_try_lock(locks, index);
            if (index == -1) l.release();
        }
    }
};

template <int I>
struct try_locker<I, false> {
    template <class... Lock>
    static void do_try_lock(const std::tuple<Lock&...>& locks, int& index)
    {
        index = I;
        unique_lock<typename variadic_types::detail::At<I, Lock...>::type> l(std::get<I>(locks), try_to_lock);

        if (l.owns_lock()) {
            index = -1;
            l.release();
        }
    }
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace mutexes
} // namespace cxx11
} // namespace srook

#    endif
#endif
