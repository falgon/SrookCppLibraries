// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_SEMAPHORE_BINARY_SEMAPHORE_HPP
#define INCLUDED_SROOK_SEMAPHORE_BINARY_SEMAPHORE_HPP

#include <srook/semaphore/semaphore.hpp>

namespace srook {
namespace semaphores {
SROOK_INLINE_NAMESPACE(v1)

template <class ConditionVariable, class Mutex, class CounterType>
class basic_binary_semaphore : public basic_semaphore<ConditionVariable, Mutex, CounterType> {
    typedef basic_binary_semaphore<ConditionVariable, Mutex, CounterType> base_type;

public:
    typedef Mutex mutex_type;
    typedef ConditionVariable condition_variable_type;
    typedef SROOK_DEDUCED_TYPENAME condition_variable_type::native_handle_type* native_handle_type;
    typedef CounterType counter_type;
    SROOK_CONSTEXPR basic_binary_semaphore() SROOK_DEFAULT
};

struct binary_semaphore
    : public basic_binary_semaphore<srook::condition_variable, srook::mutex, std::size_t> {};

SROOK_INLINE_NAMESPACE_END
} // namespace semaphores

using semaphores::basic_binary_semaphore;
using semaphores::binary_semaphore;

} // namespace srook

#endif
