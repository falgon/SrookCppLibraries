// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_NULLPTR_T
#define INCLUDED_SROOK_CONFIG_NULLPTR_T

#include <cstddef>
#include <srook/config/attribute.hpp>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/feature.hpp>

#if !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT) && !defined(nullptr)
namespace srook {
namespace cxx03 {

const class SROOK_ATTRIBUTE_TEMPLATE_VIS_DEFAULT nullptr_t {
public:
    SROOK_FORCE_INLINE SROOK_CONSTEXPR nullptr_t() {}
    SROOK_FORCE_INLINE SROOK_CONSTEXPR nullptr_t(int nat::*) {}
    SROOK_FORCE_INLINE SROOK_CONSTEXPR operator int nat::*() const { return 0; }

    template <class T>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    operator T*() const
    {
        return 0;
    }

    template <class C, class T>
    SROOK_FORCE_INLINE
    operator T C::*() const
    {
        return 0;
    }

    friend SROOK_FORCE_INLINE SROOK_CONSTEXPR 
    bool operator==(nullptr_t, nullptr_t) SROOK_NOEXCEPT_TRUE { return true; }
    friend SROOK_FORCE_INLINE SROOK_CONSTEXPR 
    bool operator!=(nullptr_t, nullptr_t) SROOK_NOEXCEPT_TRUE { return false; }

private:
    struct nat {
        int forBool;
    };
    void operator&() SROOK_EQ_DELETE
};

SROOK_FORCE_INLINE SROOK_CONSTEXPR
srook::cxx03::nullptr_t get_nullptr() { return srook::cxx03::nullptr_t(0); }

#    define nullptr srook::cxx03::get_nullptr()

} // namespace cxx03
} // namespace srook

#        define SROOK_NULLPTR_T srook::cxx03::nullptr_t
#        define SROOK_NULLPTR srook::cxx03::get_nullptr()
#    else
#        define SROOK_NULLPTR nullptr
#        define SROOK_NULLPTR_T std::nullptr_t
#    endif

#endif
