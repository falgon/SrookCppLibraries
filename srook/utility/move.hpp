#ifndef INCLUDED_SROOK_UTILITY_MOVE_HPP
#define INCLUDED_SROOK_UTILITY_MOVE_HPP
#include <srook/config/attribute/deprecated.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/config/user_config.hpp>
#include <srook/type_traits/remove_reference.hpp>
#include <srook/utility/detail/non_supported/move_semantics.hpp>

namespace srook {
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT && !defined(SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE)
namespace cxx03 {

template <class T>
struct move_tag {
    move_tag(T& value) : data_(value) {}
    T& get() const { return data_; }

private:
    T& data_;
};

} // namespace cxx03

template <class T>
cxx03::move_tag<T> move(T& t) SROOK_NOEXCEPT_TRUE
{
    return cxx03::move_tag<T>(t);
}

#elif SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT && defined(SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE)
DEF_MOVE_SEMANTICS_UTILITIES(move)

    // Deprecated message for implicit move
#    define SROOK_NO_MOVE_SEMANTICS_DEPRECATED_MESSAGE                                                                                          \
        SROOK_DEPRECATED_MESSAGE(                                                                                                               \
            "\nReason: C++03 is not supported the semantics of rvalue references. "                                                             \
            "so this function call performs an implicit move like \"std::auto_ptr\".\n"                                                         \
            "You can set to disable macro that \"SROOK_CONFIG_DISABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE\" in <srook/config/user_config.hpp>.\n" \
            "See Also: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1856.html#20.4.5%20-%20Class%20template%20auto_ptr")

#else

template <class T>
SROOK_CONSTEXPR typename srook::remove_reference<T>::type&& move(T&& t) SROOK_NOEXCEPT_TRUE
{
    return static_cast<typename srook::remove_reference<T>::type&&>(t);
}

#endif

SROOK_INLINE_NAMESPACE_END
} // namespace utility

using utility::move;

#ifndef SROOK_NO_MOVE_SEMANTICS_DEPRECATED_MESSAGE
#    define SROOK_NO_MOVE_SEMANTICS_DEPRECATED_MESSAGE
#endif

} // namespace srook
#endif
