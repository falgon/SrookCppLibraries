#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/cfenv/round_switch.hpp>
#include <srook/math/constants/algorithm/pow.hpp>

BOOST_AUTO_TEST_SUITE(srook_cfenv_round_switch_test)

BOOST_AUTO_TEST_CASE(round_switch1)
{
    namespace sc = srook::cfenv;

    SROOK_ST_ASSERT(noexcept(sc::round_switch::to_nearest()));
    SROOK_ST_ASSERT(noexcept(sc::round_switch::toward_zero()));
    SROOK_ST_ASSERT(noexcept(sc::round_switch::toward_infinity()));
    SROOK_ST_ASSERT(noexcept(sc::round_switch::toward_neg_infinity()));

    sc::round_switch::to_nearest();
    sc::round_switch::toward_zero();
    sc::round_switch::toward_infinity();
    sc::round_switch::toward_neg_infinity();
}

BOOST_AUTO_TEST_CASE(round_switch2)
{
    namespace sc = srook::cfenv;

    SROOK_ST_ASSERT(noexcept(sc::round_switch::set(std::round_to_nearest)));
    SROOK_ST_ASSERT(noexcept(sc::round_switch::set(std::round_toward_zero)));
    SROOK_ST_ASSERT(noexcept(sc::round_switch::set(std::round_toward_infinity)));
    SROOK_ST_ASSERT(noexcept(sc::round_switch::set(std::round_toward_neg_infinity)));

    sc::round_switch::set(std::round_to_nearest);
    sc::round_switch::set(std::round_toward_zero);
    sc::round_switch::set(std::round_toward_infinity);
    sc::round_switch::set(std::round_toward_neg_infinity);
}

BOOST_AUTO_TEST_CASE(round_switch3)
{
    namespace sc = srook::cfenv;
    
    // It is preferable to describe `#pragma STDC FENV_ACCESS ON` to tell the processing system access to the floating point environment, but this is not implemented in some implementations.
    // srook::cfenv::round_switch::enable_round<T>::type provides the volatile version of the type as an interim measure. 
    // This avoids optimization, but I do not think this is the best way.....
    SROOK_ST_ASSERT(srook::is_same<SROOK_DEDUCED_TYPENAME sc::round_switch::enable_round<float>::type, volatile float>::value);
    
    SROOK_IF_CONSTEXPR (srook::numeric_limits<float>::is_iec559) {
        constexpr int pow23 = srook::math::pow(2, 23);
        volatile float fp = pow23;
        
        // srook::cfenv::round_switch::scoped_set supports switching of floating-point rounding method with scope guard.
        // Generally, we recommend using such a scope guard function in consideration of exception safety.
        sc::round_switch::scoped_set(std::round_toward_infinity, std::round_to_nearest, [] (volatile float f) noexcept {
                BOOST_CHECK_EQUAL(f + .1f, pow23 + 1); // This assertion must always true because the rounding style of floating point is toward_infinity only in this block.
        }, fp); // When exiting from this block, the rounding style is set to nearest. 
        BOOST_CHECK_EQUAL(fp + .1f, pow23); // This assertion must always true because the rounding style of floating point is nearest in this section.

        sc::round_switch::scoped_set(std::round_toward_zero, std::round_toward_neg_infinity, [] (volatile float f) noexcept {
                BOOST_CHECK_EQUAL(f + .1f, pow23); // toward zero
        }, fp);
        BOOST_CHECK_EQUAL(fp + .1f, pow23); // toward neg intinity
        sc::round_switch::to_nearest();
    }
}

BOOST_AUTO_TEST_CASE(round_switch4)
{
    namespace sc = srook::cfenv;
    
    SROOK_IF_CONSTEXPR (srook::numeric_limits<float>::is_iec559) {
        constexpr int pow23 = srook::math::pow(2, 23);
        volatile float fp = pow23;
        {
            // srook::cfenv::round_switch::make_scoped returns an object with the features of switching floating point rounding method by scope guard.
            // The type of this object is srook::scope::unique_resource<R, D>.
            SROOK_ATTRIBUTE_UNUSED const auto resource = sc::round_switch::make_scoped(std::round_toward_infinity, std::round_to_nearest); 
            
            BOOST_CHECK_EQUAL(fp + .1f, pow23 + 1); // toward infinity
        } // When exiting from this block, the rounding style is set to nearest.
        BOOST_CHECK_EQUAL(fp + .1f, pow23); // to nearest
    }
}

BOOST_AUTO_TEST_SUITE_END()
