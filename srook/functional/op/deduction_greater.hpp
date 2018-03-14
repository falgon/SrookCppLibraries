#ifndef INCLUDED_SROOK_FUNCTIONAL_DEDUCTION_GREATER_HPP
#define INCLUDED_SROOK_FUNCTIONAL_DEDUCTION_GREATER_HPP
#include <srook/functional/op/deduction_less_equal.hpp>

namespace srook {
namespace functional {
inline namespace v1 {

struct deduction_greater {
    template <class first_argument_type, class second_argument_type>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR_OR_CONST bool
    operator()(const first_argument_type& lhs, const second_argument_type& rhs)
    const SROOK_NOEXCEPT(srook::functional::deduction_less_equal(lhs, rhs))
    {
        return !srook::functional::deduction_less_equal()(lhs, rhs);
    }
};

} // namespace v1
} // namespace functional

using functional::deduction_greater;

} // namespace srook

#endif
