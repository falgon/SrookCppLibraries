#ifndef INCLUDED_SROOK_FUNCTIONAL_DEDUCTION_NEGATE_HPP
#define INCLUDED_SROOK_FUNCTIONAL_DEDUCTION_NEGATE_HPP
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <type_traits>

namespace srook {
namespace functional {
inline namespace v1 {

struct deduction_negate {
    template <class argument_type>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR_OR_CONST argument_type operator()(const argument_type& arg) const SROOK_NOEXCEPT_TRUE
    {
        return return_type(-arg);
    }
};

} // namespace v1
} // namespace functional

using functional::deduction_negate;

} // namespace srook

#endif
