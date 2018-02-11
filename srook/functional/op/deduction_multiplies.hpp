#ifndef INCLUDED_SROOK_FUNCTIONAL_DEDUCTION_MULTIPLIES_HPP
#define INCLUDED_SROOK_FUNCTIONAL_DEDUCTION_MULTIPLIES_HPP
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <type_traits>

namespace srook {
namespace functional {
inline namespace v1 {

struct deduction_multiplies {
    template <class first_argument_type, class second_argument_type>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR_OR_CONST typename std::common_type<first_argument_type, second_argument_type>::type
    operator()(const first_argument_type& lhs, const second_argument_type& rhs)
        const SROOK_NOEXCEPT(noexcept(typename std::common_type<first_argument_type, second_argument_type>::type(lhs) * typename std::common_type<first_argument_type, second_argument_type>::type(rhs)))
    {
        typedef typename std::common_type<first_argument_type, second_argument_type>::type return_type;
        return return_type(lhs * rhs);
    }
};

} // namespace v1
} // namespace functional

using functional::deduction_multiplies;

} // namespace srook

#endif
