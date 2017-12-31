// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_OPTIONAL_NULLOPT_HPP
#define INCLUDED_SROOK_OPTIONAL_NULLOPT_HPP
#include <exception>
#include <initializer_list>
#include <srook/config/feature.hpp>
#include <srook/type_traits.hpp>

namespace srook {
namespace optionally {
SROOK_INLINE_NAMESPACE(v1)

struct nullopt_t {
    SROOK_STRONG_ENUM_BEGIN(Construct) {
        Token
    };
    SROOK_STRONG_ENUM_EPILOG(Construct)
    explicit SROOK_CONSTEXPR_OR_CONST nullopt_t(Construct) {}
};
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR nullopt_t nullopt(nullopt_t::Construct::Token);

SROOK_INLINE_NAMESPACE_END
} // namespace optionally

using optionally::nullopt_t;
using optionally::nullopt;

} // namespace srook
#endif
