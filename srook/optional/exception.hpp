// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_OPTIONAL_EXCEPTION_HPP
#define INCLUDED_SROOK_OPTIONAL_EXCEPTION_HPP

#include <srook/config.hpp>
#include <stdexcept>

namespace srook {
namespace optionally {
SROOK_INLINE_NAMESPACE(v1)

class bad_optional_access : public std::exception {
public:
    bad_optional_access() SROOK_DEFAULT

    virtual const char* what() const
    SROOK_NOEXCEPT_TRUE SROOK_OVERRIDE
    {
        return "bad optional access";
    }

    virtual ~bad_optional_access() SROOK_NOEXCEPT_TRUE SROOK_DEFAULT
};

namespace detail {

SROOK_FORCE_INLINE SROOK_NORETURN void throw_bad_optional_access() { SROOK_THROW bad_optional_access(); }

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} // namespace optionally

using optionally::bad_optional_access;

} // namespace srook
#endif
