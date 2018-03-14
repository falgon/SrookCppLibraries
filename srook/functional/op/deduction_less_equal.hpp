#ifndef INCLUDED_SROOK_FUNCTIONAL_DEDUCTION_LESS_EQUAL_HPP
#define INCLUDED_SROOK_FUNCTIONAL_DEDUCTION_LESS_EQUAL_HPP
#include <srook/functional/op/deduction_less.hpp>

namespace srook {
namespace functional {
inline namespace v1 {

struct deduction_less_equal {
    template <class first_argument_type, class second_argument_type>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR_OR_CONST bool
    operator()(const first_argument_type& lhs, const second_argument_type& rhs)
    const SROOK_NOEXCEPT(
        (static_cast<typename std::common_type<
            first_argument_type, 
            second_argument_type
        >::type>(declval<first_argument_type>()) == static_cast<typename std::common_type<
            first_argument_type, 
            second_argument_type
        >::type>(declval<second_argument_type>())) || srook::functional::deduction_less()(lhs, rhs)
    )
    {
        typedef typename std::common_type<first_argument_type, second_argument_type>::type return_type;
        return static_cast<return_type>(lhs) == static_cast<return_type>(rhs) || deduction_less()(lhs, rhs);
    }
};

} // namespace v1
} // namespace functional

using functional::deduction_less_equal;

} // namespace srook

#endif
