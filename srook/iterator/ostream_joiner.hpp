#ifndef INCLUDED_SROOK_ITERATOR_OSTREAM_JOINER_HPP
#define INCLUDED_SROOK_ITERATOR_OSTREAM_JOINER_HPP

#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#if SROOK_CPLUSPLUS <= SROOK_CPLUSPLUS11_CONSTANT
#if __has_include(<bits/c++14_warning.h>)
#	include <bits/c++14_warnings.h>
#endif
#else
#	include <iosfwd>
#	include <iterator>
#	include <type_traits>
#	include <srook/config/noexcept_detection.hpp>
#	include <srook/config/attribute/force_inline.hpp>
#	include <srook/config/feature/inline_namespace.hpp>
#   include <srook/memory/addressof.hpp>
#   include <srook/utility/move.hpp>
#   include <srook/utility/forward.hpp>
#   include <srook/type_traits/decay.hpp>

namespace srook {
namespace iterator {
SROOK_INLINE_NAMESPACE(fundamentals_v2)

template <class Delim, typename CharT = char, class Traits = std::char_traits<CharT>>
struct ostream_joiner {
    typedef CharT char_type;
    typedef Traits traits_type;
    typedef std::basic_ostream<CharT, Traits> ostream_type;
    typedef std::output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    ostream_joiner(ostream_type& os, Delim delimiter) SROOK_NOEXCEPT(std::is_nothrow_copy_constructible<Delim>::value)
	    : out(srook::addressof(os)), delim(srook::move(delimiter)) {}

    template <typename T>
    ostream_joiner<Delim, CharT, Traits>& operator=(const T &value)
    SROOK_NOEXCEPT(declval<std::basic_ostream<CharT, Traits>*>() << declval<Delim>())
    {
        if (!first) *out << delim;
        first = false;
        *out << value;
        return *this;
    }

    ostream_joiner<Delim, CharT, Traits>& operator*() SROOK_NOEXCEPT_TRUE { return *this; }
    ostream_joiner<Delim, CharT, Traits>& operator++() SROOK_NOEXCEPT_TRUE { return *this; }
    ostream_joiner<Delim, CharT, Traits>& operator++(int) SROOK_NOEXCEPT_TRUE { return *this; }
private:
	bool first = true;
    std::basic_ostream<CharT, Traits>* out;
    const Delim delim;
};

template <typename CharT, class Traits, class Delim>
SROOK_FORCE_INLINE ostream_joiner<SROOK_DEDUCED_TYPENAME decay<Delim>::type, CharT, Traits> 
make_ostream_joiner(std::basic_ostream<CharT, Traits>& os, Delim&& delimiter)
{
    return ostream_joiner<SROOK_DEDUCED_TYPENAME decay<Delim>::type>(os, srook::forward<Delim>(delimiter));
}


SROOK_INLINE_NAMESPACE_END
} // namespace iterator

using iterator::ostream_joiner;
using iterator::make_ostream_joiner;

} // namespace srook

#endif
#endif
