// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_ALGORITHM_ENCODING_LZ77_CONFIG_HPP
#define INCLUDED_SROOK_ALGORITHM_ENCODING_LZ77_CONFIG_HPP

#include <srook/config.hpp>
#include <srook/type_traits.hpp>
#include <string>

namespace srook {
namespace algorithm {
namespace encoding {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, class = SROOK_DEDUCED_TYPENAME voider<void>::type>
struct is_index_accessible : SROOK_FALSE_TYPE {};
template <class T>
struct is_index_accessible<T, SROOK_DEDUCED_TYPENAME voider<SROOK_DECLTYPE(declval<T>().operator[](0))>::type>
    : SROOK_TRUE_TYPE {};

#if 1

template <class String>
struct string_require {
    typedef type_traits::detail::Lor<
                type_traits::detail::Land<
                    type_traits::detail::Lor<is_pointer<SROOK_DEDUCED_TYPENAME decay<String>::type>, is_array<SROOK_DEDUCED_TYPENAME decay<String>::type>>,
                    is_character<SROOK_DEDUCED_TYPENAME decay<String>::type>
                >,
                type_traits::detail::Land<
                    detail::is_index_accessible<SROOK_DEDUCED_TYPENAME decay<String>::type>, 
                    is_character<SROOK_DEDUCED_TYPENAME decay<String>::type::value_type>
                >
            > 
            type;
};

#elif // C++20 concept

template <class String>
concept StringType = requires (String x) { x[0]; } && type_traits::detail::Lor<is_character<decay_t<String>>, is_character<decay_t<String>::value_type>>::value;

#endif

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} // namespace encoding
} // namespace algorithm
} // namespace srook

#endif
